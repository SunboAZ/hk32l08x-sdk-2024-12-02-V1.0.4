/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  usb_pwr.c
* @brief:     Connection/disconnection & power management.
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "usb_pwr.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t bDeviceState = UNCONNECTED; /* USB device status */
__IO bool fSuspendEnabled = TRUE;  /* true when suspend is possible */
__IO uint32_t EP[8];

struct
{
    __IO RESUME_STATE eState;
    __IO uint8_t bESOFcnt;
}
ResumeS;

__IO uint32_t remotewakeupon = 0;

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Extern function prototypes ------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Power on
  * @retval USB_SUCCESS.
  */
RESULT PowerOn(void)
{
    uint16_t wRegVal;

#if !defined (USE_NUCLEO)

    /*** cable plugged-in ***/
    USB_Cable_Config(ENABLE);
#endif

    /*** CNTR_FRES = 1 ***/
    wRegVal = CNTR_FRES;
    _SetCNTR(wRegVal);

    /* The following sequence is recommended:
      1- FRES = 0
      2- Wait until RESET flag = 1 (polling)
      3- clear ISTR register */

    /*** CNTR_FRES = 0 ***/
    wInterrupt_Mask = 0;

    _SetCNTR(wInterrupt_Mask);

    /* Wait until RESET flag = 1 (polling) */
    while ((_GetISTR()&ISTR_RESET) == 1)
    {
    }

    /*** Clear pending interrupts ***/
    SetISTR(0);

    /*** Set interrupt mask ***/
    wInterrupt_Mask = CNTR_RESETM | CNTR_SUSPM | CNTR_WKUPM;
    _SetCNTR(wInterrupt_Mask);

    return USB_SUCCESS;
}

/**
  * @brief  handles switch-off conditions
  * @retval USB_SUCCESS.
  */
RESULT PowerOff(void)
{
    /* disable all interrupts and force USB reset */
    _SetCNTR(CNTR_FRES);

    /* clear interrupt status register */
    _SetISTR(0);

#if !defined (USE_NUCLEO)

    /* Disable the Pull-Up*/
    USB_Cable_Config(DISABLE);
#endif

    /* switch-off device */
    _SetCNTR(CNTR_FRES);

    /* sw variables reset
       ... */

    return USB_SUCCESS;
}

/**
  * @brief  sets suspend mode operating conditions
  * @retval USB_SUCCESS.
  */
void Suspend(void)
{
    uint32_t i = 0;
    uint16_t wCNTR;
#ifdef USB_LOW_PWR_MGMT_SUPPORT
    uint32_t tmpreg = 0;
    __IO uint32_t savePWR_CR = 0;
#endif /* USB_LOW_PWR_MGMT_SUPPORT */


    /* suspend preparation
       ... */

    /*Store CNTR value */
    wCNTR = _GetCNTR();

    /* This a sequence to apply a force RESET to handle a robustness case */

    /*Store endpoints registers status */
    for (i = 0; i < 8; i++)
    {
        EP[i] = _GetENDPOINT(i);
    }

    /* unmask RESET flag */
    wCNTR |= CNTR_RESETM;
    _SetCNTR(wCNTR);

    /*apply FRES */
    wCNTR |= CNTR_FRES;
    _SetCNTR(wCNTR);

    /*clear FRES*/
    wCNTR &= ~CNTR_FRES;
    _SetCNTR(wCNTR);

    /*poll for RESET flag in ISTR*/
    while ((_GetISTR()&ISTR_RESET) == 0)
    {
    }

    /* clear RESET flag in ISTR */
    _SetISTR((uint16_t)CLR_RESET);

    /*restore Enpoints*/
    for (i = 0; i < 8; i++)
        _SetENDPOINT(i, EP[i]);

    /* Now it is safe to enter macrocell in suspend mode */
    wCNTR |= CNTR_FSUSP;
    _SetCNTR(wCNTR);

#ifdef USB_LOW_PWR_MGMT_SUPPORT

    /*prepare entry in low power mode (STOP mode)
      Select the regulator state in STOP mode*/
    savePWR_CR = PWR->CR;
    tmpreg = PWR->CR;

    /* Clear PDDS and LPDS bits */
    tmpreg &= ((uint32_t)0xFFFFFFFC);

    /* Set LPDS bit according to PWR_Regulator value */
    tmpreg |= PWR_Regulator_LowPower;

    /* Store the new value */
    PWR->CR = tmpreg;

    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR |= 0x04;

    /* enter system in STOP mode, only when wakeup flag in not set */
    if ((_GetISTR()&ISTR_WKUP) == 0)
    {
        __WFI();

        /* Reset SLEEPDEEP bit of Cortex System Control Register */
        SCB->SCR &= (uint32_t)~((uint32_t)0x04);
    }
    else
    {
        /* Clear Wakeup flag */
        _SetISTR(CLR_WKUP);

        /* clear FSUSP to abort entry in suspend mode  */
        wCNTR = _GetCNTR();
        wCNTR &= ~CNTR_FSUSP;
        _SetCNTR(wCNTR);

        /*restore sleep mode configuration
          restore Power regulator config in sleep mode*/
        PWR->CR = savePWR_CR;

        /* Reset SLEEPDEEP bit of Cortex System Control Register */
        SCB->SCR &= (uint32_t)~((uint32_t)0x04);
    }

#endif /* USB_LOW_PWR_MGMT_SUPPORT */
}

/**
  * @brief  Handles wake-up restoring normal operations
  * @retval USB_SUCCESS.
  */
void Resume_Init(void)
{
    /* ------------------ ONLY WITH BUS-POWERED DEVICES ----------------------
       restart the clocks
       ...  */

#ifdef USB_LOW_PWR_MGMT_SUPPORT

    /* restore full power
     ... on connected devices */
    Leave_LowPowerMode();

#endif /* USB_LOW_PWR_MGMT_SUPPORT */

    /* reset FSUSP bit */
    _SetCNTR(IMR_MSK);

    /* reverse suspend preparation */

    /* ... */

}

/**
  * @brief  This is the state machine handling resume operations and
  *         timing sequence. The control is based on the Resume structure
  *         variables and on the ESOF interrupt calling this subroutine
  *         without changing machine state.
  * @param  a state machine value (RESUME_STATE)
  *         RESUME_ESOF doesn't change ResumeS.eState allowing
  *         decrementing of the ESOF counter in different states.
  * @retval None.
  */
void Resume(RESUME_STATE eResumeSetVal)
{
    uint16_t wCNTR;

    if (eResumeSetVal != RESUME_ESOF)
    {
        ResumeS.eState = eResumeSetVal;
    }

    switch (ResumeS.eState)
    {
        case RESUME_EXTERNAL:
            if (remotewakeupon == 0)
            {
                Resume_Init();
                ResumeS.eState = RESUME_OFF;
            }
            else /* RESUME detected during the RemoteWAkeup signalling => keep RemoteWakeup handling*/
            {
                ResumeS.eState = RESUME_ON;
            }

            break;

        case RESUME_INTERNAL:
            Resume_Init();
            ResumeS.eState = RESUME_START;
            remotewakeupon = 1;
            break;

        case RESUME_LATER:
            ResumeS.bESOFcnt = 2;
            ResumeS.eState = RESUME_WAIT;
            break;

        case RESUME_WAIT:
            ResumeS.bESOFcnt--;

            if (ResumeS.bESOFcnt == 0)
            {
                ResumeS.eState = RESUME_START;
            }

            break;

        case RESUME_START:
            wCNTR = _GetCNTR();
            wCNTR |= CNTR_RESUME;
            _SetCNTR(wCNTR);
            ResumeS.eState = RESUME_ON;
            ResumeS.bESOFcnt = 10;
            break;

        case RESUME_ON:
            ResumeS.bESOFcnt--;

            if (ResumeS.bESOFcnt == 0)
            {
                wCNTR = _GetCNTR();
                wCNTR &= (~CNTR_RESUME);
                _SetCNTR(wCNTR);
                ResumeS.eState = RESUME_OFF;
                remotewakeupon = 0;
            }

            break;

        case RESUME_OFF:
        case RESUME_ESOF:
        default:
            ResumeS.eState = RESUME_OFF;
            break;
    }
}

/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/

