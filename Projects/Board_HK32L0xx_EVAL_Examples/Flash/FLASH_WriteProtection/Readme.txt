/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2024-01-04
1.�״η���

******************************������ϸ����*****************************
��������:
					1. ��ʾ��������ο����͹ر�FLASH��д������
						 - ����д����:
							 Ҫ����д��������main.c�ļ���ע��"#define WRITE_PROTECTION_DISABLE"
							 ȡ��ע��"#define WRITE_PROTECTION_ENABLE"��Ĭ�ϣ���		
							 Ϊ��ʹ��ĳ��ҳд�������û��������FLASH_EnableWriteProtection������
							 �ú����Ĳ���������Ҫ������ҳ������Ȼ��ʹ��FLASH_OB_Launch()������
							 ��ϵͳ���ã������µ�ѡ���ֽ�ֵ��
					   - ȡ��д����:
               Ҫ����д��������main.c�ļ���ע��"#define WRITE_PROTECTION_ENABLE"
							 ȡ��ע��"#define WRITE_PROTECTION_DISABLE"��	
               Ҫ����Flash��д��������Ҫ����ѡ���ֽڡ��ò�����FLASH_OptionByteErase������ɡ�
               Ȼ��ʹ��FLASH_OB_Launch()��������ϵͳ���ã������µ�ѡ���ֽ�ֵ��
					2.  �������д����������FLASH_PAGES_TO_BE_PROTECTEDѡ���flashҳʹ��д����������
							ҳ�Ķ�����״̬����ԭ����
              ���ȡ��д����������FLASH_PAGES_TO_BE_PROTECTEDѡ���flashҳȡ��д����������
							ҳ�Ķ�����״̬����ԭ����				
							�����ж����FLASH_PAGES_TO_BE_PROTECTEDѡ���flashҳû��д��������ִ�в�����д
							������ͨ��MemoryProgramStatus����ȷ�ϳ���ִ�������
ʱ������:
	�����̲���HSE+PLL48MHz��Ϊϵͳʱ�ӣ��û������Ҫ����ϵͳʱ�����ã���ο���Ӧ�û��ֲ����
	RCC�⺯����RCC������̡�

����оƬ:
	HK32L0xxȫϵ��

�漰����:
	Flash
	
�漰�ܽ�:	
	��

ע������:
	1. �Ƽ�ʹ��MDK5.00�������ϰ汾���뱾���̣�MDK-ARM��
	          ����IAR8.22�������ϰ汾���뱾����(EWARM);
	2. ʹ��֮ǰ����ԴVCC��GND���Ƿ�������
���ʹ��:
	1. ֱ�ӱ���������ص������棬����������;
	2. ȷ�ϱ���MemoryProgramStatus�Ƿ�ΪFAILED��ʾд����ʹ����Ч��flash��дʧ�ܣ�
		 ��main.c�ļ���ע��"#define WRITE_PROTECTION_ENABLE"��ȡ��ע��"#define WRITE_PROTECTION_DISABLE"
		 �ٱ������ص������棬���������档	ȷ�ϱ���MemoryProgramStatus�Ƿ�ΪPASSED��ʾд����ȡ���ɹ���
		 flash��д�ɹ���
***********************************************************************