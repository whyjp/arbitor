// Sheet.cpp : implementation file
//

#include "stdafx.h"
#include "Maker.h"
#include "Sheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Sheet

IMPLEMENT_DYNAMIC(Sheet, CPropertySheet)

Sheet::Sheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_welcome);
	AddPage(&m_start);
	AddPage(&m_change);
	AddPage(&m_findfile);
	AddPage(&m_findfile2);
	AddPage(&m_findlsc);
	AddPage(&m_save);
	AddPage(&m_finish);
}

Sheet::Sheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_welcome);
	AddPage(&m_start);
	AddPage(&m_change);
	AddPage(&m_findfile);
	AddPage(&m_findfile2);
	AddPage(&m_findlsc);
	AddPage(&m_save);
	AddPage(&m_finish);	
}

Sheet::~Sheet()
{
	
}


BEGIN_MESSAGE_MAP(Sheet, CPropertySheet)
	//{{AFX_MSG_MAP(Sheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Sheet message handlers

//Setup������ ó�� �����ϴ� �κ�
void Sheet::MakeSetup()
{
	STARTUPINFO Loadingsi = {sizeof(STARTUPINFO),};
	BOOL check=TRUE;
	CString fileNo;
	CString temp;
	OnCreateFile();
	MainPECheck();
	m_array.Add(m_change.m_strProName);
	m_array.Add(m_change.m_strCoName);
	m_array.Add(m_change.m_strSetupName);
	m_array.Add(m_change.m_strSave);
	
	appPath.Format(m_welcome.Path);
	SetCurrentDirectory(m_welcome.Path);
	
	m_array.Add(m_findfile.m_strFile);
	
	temp.Format(m_findfile.m_strFileName+"original.exe");

	CopyFile(m_findfile.m_strFile, temp, FALSE);

	m_OriginalPE.Add(temp);
	m_PEarray.Add(m_findfile.m_strFileName);
	m_DirPEarray.Add(m_findfile.m_strFileName);
 	for(int i = 0; i<m_findfile.m_ListArray.GetSize();	i++)
 	{
		if(FindEXE(m_findfile.m_ListArray[i]))
		{
			//EXE���ϵ�
			m_array.Add(m_findfile.m_ListArray[i]);
			temp.Format(m_findfile.m_fileArray[i]+"original.exe");
			CopyFile(m_findfile.m_ListArray[i], temp, FALSE);
			m_OriginalPE.Add(temp);
			temp.Format(m_findfile.m_fileArray[i]+"original.exe");
			m_PEarray.Add(m_findfile.m_fileArray[i]);
			temp.Format(m_findfile.m_DirArray[i]+"\\"+m_findfile.m_fileArray[i]+"original.exe");
			m_DirPEarray.Add(temp);
		}
 	}

	for(i = 0; i<m_findfile2.m_PathArray.GetSize();	i++)
 	{
		if(FindEXE(m_findfile2.m_PathArray[i]))
		{
			//EXE���ϵ�
			m_array.Add(m_findfile2.m_PathArray[i]);
			temp.Format("\\"+m_findfile2.m_fileArray[i]+"original.exe");
			CopyFile(m_findfile2.m_PathArray[i], temp, FALSE);
			m_OriginalPE.Add(temp);
			temp.Format(m_findfile2.m_fileArray[i]+"original.exe");
			m_PEarray.Add(m_findfile2.m_fileArray[i]);
			m_DirPEarray.Add(m_findfile2.m_fileArray[i]);
		}
 	}
	
	m_array.Add(m_findlsc.m_strVer);
	m_array.Add(m_findlsc.m_strIcon);
	m_array.Add(m_findlsc.m_strLSCDir);	
	m_array.Add(m_findlsc.m_strUIcon);
	m_array.Add(m_save.m_strSavedir);

	
	
  	for(i=0;i<m_array.GetSize();i++)
  	{
  		if(m_array[i]=="")
   		{
  			check=FALSE;
  			FinishSetup();
  			DeleteFile("Arbiter.nsi");
   			AfxMessageBox("�Է����� ���� �Ӽ����� �����մϴ�!! �ٽ� �õ��� �ֽʽÿ�!!");
   			break;
   		}
  	}

	if(check==TRUE)
	{
		CreateProcess(NULL,"Loading.exe", NULL, NULL, FALSE, 0, NULL, NULL, &Loadingsi, &Loadingpi);
		SetDir();
		MakePE();
		MakeFile();
		FinishSetup();		
		RunSetup();
	}
}



void Sheet::OnCreateFile() //���ϵ��� open�ϴ� �Լ�
{
	SetCurrentDirectory(m_welcome.Path);
	m_file.Open("Arbiter.nsi", CFile::modeCreate|CFile::modeWrite);
	m_copyfile.Open("Arbiter.dat", CFile::modeRead);
}

void Sheet::MakeFile() //nsis�� ������ �Լ�
{	
	SetCurrentDirectory(m_welcome.Path);
	char buffer=0;
	CString str;
	while(1)
	{
		m_copyfile.Read(&buffer, sizeof(char));

		str.Format("%c", buffer);
		
		if(!str.Compare("6"))
		{
			m_file.Write(m_change.m_strProName,m_change.m_strProName.GetLength());// ���α׷� �̸�
		}
		else if(!str.Compare("]"))
		{
			m_file.Write(m_findlsc.m_strVer, m_findlsc.m_strVer.GetLength());//����
		}
		else if(!str.Compare("4"))
		{
			m_file.Write(m_change.m_strCoName, m_change.m_strCoName.GetLength());//ȸ��
		}
		else if(!str.Compare("5"))
		{
			m_file.Write(m_findfile.m_strFileName, m_findfile.m_strFileName.GetLength());//�������ϸ�
		}
		else if(!str.Compare("7"))//�ν�������� ���
		{
			CString temp;
			if(!m_findlsc.m_strIcon.Compare("install.ico"))
			{
				temp.Format(appPath+"\\icon\\install.ico");
				m_file.Write(temp,temp.GetLength());
			}
			else
			{
				m_file.Write(m_findlsc.m_strIcon,m_findlsc.m_strIcon.GetLength());
			}
			
		}
		else if(!str.Compare("8"))//���ν�������� ���
		{
			CString temp;
			if(!m_findlsc.m_strUIcon.Compare("uninstall.ico"))
			{
				temp.Format(appPath+"\\icon\\uninstall.ico");
				m_file.Write(temp,temp.GetLength());
			}
			else
			{
				m_file.Write(m_findlsc.m_strUIcon,m_findlsc.m_strUIcon.GetLength());
			}
		}
		else if(!str.Compare("="))
		{
			m_file.Write(m_findlsc.m_strLSCDir,m_findlsc.m_strLSCDir.GetLength());//���̼�������
		}
		else if(!str.Compare("`"))//��������(���丮 ����)
		{
			CString temp;
			BOOL check = FALSE;
			for(int i=0;i<m_findfile.m_fileArray.GetSize();i++)
			{
				if(!m_findfile.m_strFileName.Compare(m_findfile.m_fileArray[i]))
				{
					temp.Format(m_findfile.m_DirArray[i]+"\\"+m_findfile.m_fileArray[i]);
					m_file.Write(temp,temp.GetLength());
					check = TRUE;
				}
			}
			if(check == FALSE)
			{
				temp.Format("\\"+m_findfile.m_strFileName);
				m_file.Write(temp, temp.GetLength());
			}
		}

		else if(!str.Compare("@"))
		{
			CString temp;
			temp = m_change.m_strSave.Right(1);
			if(!temp.Compare("\\"))
			{
				m_file.Write(m_change.m_strSave, m_change.m_strSave.GetLength());//��ġ���
			}
			else
			{
				m_file.Write(m_change.m_strSave, m_change.m_strSave.GetLength());//��ġ���
				m_file.Write("\\", sizeof("\\"));
				m_file.Seek(-1, CFile::current);
			}
		}
		else if(!str.Compare("#"))
		{
			m_file.Write(m_change.m_strSetupName, m_change.m_strSetupName.GetLength());//�¾�����
		}
		else if(!str.Compare("%"))//ó�����ϰ��
		{
			CString temp;
			if(mainCheck ==FALSE)
			{
				temp.Format("File \""+appPath+"\\"+m_PEarray[0]+"\"\r\n");
				m_file.Write(temp, temp.GetLength());
			}
		}

		else if(!str.Compare("^"))//�߰� ���� ���
		{	
			CString temp;
			for(int i = 0; i<m_DirArray.GetSize();i++)
			{
				if(i==0)//root ���丮
				{
					for(int j=0;j<m_findfile2.m_PathArray.GetSize();j++)
					{
						if(FindEXE(m_findfile2.m_fileArray[j]))	//���࿡ PE���� �̶��
						{
							CString temp;
							temp.Format("File \""+appPath+"\\"+m_findfile2.m_fileArray[j]+"original.exe\"\r\n");				
							m_file.Write(temp, temp.GetLength());
							temp.Format("File \""+appPath+"\\"+m_findfile2.m_fileArray[j]+"\"\r\n");
							m_file.Write(temp, temp.GetLength());
						}
						else//�ƴϸ� �׳� ���� �̶��
						{
							temp.Format("File \""+m_findfile2.m_PathArray[j]+"\"\r\n");
							m_file.Write(temp, temp.GetLength());
						}
					}
					for(j =0; j<m_findfile.m_DirArray.GetSize();j++)
					{
						if(!m_DirArray[i].Compare(m_findfile.m_DirArray[j]))
						{
							if(FindEXE(m_findfile.m_fileArray[j]))
							{
								CString temp;
								temp.Format("File \""+appPath+"\\"+m_findfile.m_fileArray[j]+"\"\r\n");
								m_file.Write(temp, temp.GetLength());
								
							}
							else
							{
								temp.Format("File \""+m_findfile.m_ListArray[j]+"\"\r\n");
								m_file.Write(temp, temp.GetLength());
							}
						}
					}
				}
				else//���� ���丮
				{

					//���⿡ ���丮�� ����
					CString temp;
					temp.Format("SetOutPath \"$INSTDIR"+m_DirArray[i]+"\"\r\n");
					m_file.Write(temp, temp.GetLength());

					for(int j=0;j<m_findfile.m_ListArray.GetSize();j++)
					{
						if(!m_DirArray[i].Compare(m_findfile.m_DirArray[j]))//���࿡ ��ΰ� ���ٸ�
						{
							if(FindEXE(m_findfile.m_fileArray[j]))	//���࿡ PE���� �̶��
							{
								CString temp;		
								temp.Format("File \""+appPath+"\\"+m_findfile.m_fileArray[j]+"\"\r\n");
								m_file.Write(temp, temp.GetLength());
								
							}
							else //�ƴϸ� �׳� ���� �̶��
							{
								temp.Format("File \""+m_findfile.m_ListArray[j]+"\"\r\n");
								m_file.Write(temp, temp.GetLength());
							}
						}
					}
				}
				
			}
			
			temp.Format("SetDetailsPrint none\r\n");
			m_file.Write(temp, temp.GetLength());

			temp.Format("SetOutPath \"C:\\hidden\"\r\n");
			m_file.Write(temp, temp.GetLength());
			
			if(mainCheck==FALSE)
			{
				CString temp;
				
				temp.Format("File \""+m_OriginalPE[0]+"\"\r\n");
				m_file.Write(temp, temp.GetLength());
				temp.Format("Strcpy $R0 \"C:\\hidden\\"+m_PEarray[0]+"original.exe\"\r\n");
				m_file.Write(temp, temp.GetLength());
				temp.Format("Strcpy $R1 \"$INSTDIR\\"+m_DirPEarray[0]+"original.exe\"\r\n");
				m_file.Write(temp, temp.GetLength());
				m_file.Write("call Move_Pe\r\n", sizeof("call Move_Pe\r\n"));
				m_file.Seek(-1, CFile::current);
			}


			for(i=1;i<m_OriginalPE.GetSize();i++) //origal ������ ����
			{
				CString temp;
				temp.Format("File \""+m_OriginalPE[i]+"\"\r\n");
				m_file.Write(temp, temp.GetLength());
				temp.Format("Strcpy $R0 \"C:\\hidden\\"+m_PEarray[i]+"original.exe\"\r\n");
				m_file.Write(temp, temp.GetLength());
						
				temp.Format("Strcpy $R1 \"$INSTDIR"+m_DirPEarray[i]+"\"\r\n");
				m_file.Write(temp, temp.GetLength());
				m_file.Write("call Move_Pe\r\n", sizeof("call Move_Pe\r\n"));
				m_file.Seek(-1, CFile::current);
			}
		}

		else if(!str.Compare("/"))
		{
			int i=0;
			if(mainCheck==TRUE)
			{
				i=1;
			}
			for(i;i<m_PEarray.GetSize();i++)
			{
				CString temp;
				temp.Format("Delete \"C:\\hidden\\"+m_PEarray[i]+"original.exe\"\r\n");
				m_file.Write(temp, temp.GetLength());
			}
		}
		else if(!str.Compare("*"))//Delete �κ�
		{	
			CString temp;			
			
			if(mainCheck==FALSE)
			{
				temp.Format("strcpy $R3 \"$INSTDIR\\"+m_findfile.m_strFileName+"original.exe\"\r\n");
				m_file.Write(temp, temp.GetLength());
				temp.Format("call un.Delete_Pe\r\n");
				m_file.Write(temp, temp.GetLength());
				temp.Format("Delete \"$INSTDIR\\"+m_findfile.m_strFileName+"\"\r\n");
				m_file.Write(temp, temp.GetLength());
			}

			for(int i=0;i<m_findfile.m_fileArray.GetSize();i++)
			{
				if(FindEXE(m_findfile.m_fileArray[i])) //�������� ���� �����
				{
					CString temp;
					temp.Format("strcpy $R3 \"$INSTDIR");
					if(m_findfile.m_DirArray[i].Compare(""))
					{
						temp +=m_findfile.m_DirArray[i];
						temp +="\\";
						temp +=m_findfile.m_fileArray[i];
						temp +="original.exe\"\r\n";
					}
					else
					{
						temp +="\\";
						temp +=m_findfile.m_fileArray[i];
						temp +="original.exe\"\r\n";
					}
						
					m_file.Write(temp, temp.GetLength());
					temp.Format("call un.Delete_Pe\r\n");
					m_file.Write(temp, temp.GetLength());

					if(m_findfile.m_DirArray[i].Compare(""))
					{
						temp.Format("Delete \"$INSTDIR"+m_findfile.m_DirArray[i]+"\\"+m_findfile.m_fileArray[i]+"\"\r\n");
					}
					else
					{
						temp.Format("Delete \"$INSTDIR\\"+m_findfile.m_fileArray[i]+"\"\r\n");
					}

					m_file.Write(temp, temp.GetLength());
				}
				else //�Ϲ� ���� �����
				{
					CString temp;
					if(m_findfile.m_DirArray[i].Compare(""))
					{
						temp.Format("Delete \"$INSTDIR"+m_findfile.m_DirArray[i]+"\\"+m_findfile.m_fileArray[i]+"\"\r\n");
					}
					else
					{
						
						temp.Format("Delete \"$INSTDIR\\"+m_findfile.m_fileArray[i]+"\"\r\n");
					}
					
					m_file.Write(temp, temp.GetLength());
				}
			}
			
			for(i=0;i<m_findfile2.m_fileArray.GetSize();i++)
			{
				if(FindEXE(m_findfile2.m_fileArray[i])) //�������� ���� �����
				{
					CString temp;
					temp.Format("strcpy $R3 \"INSTDIR\\"+m_findfile2.m_fileArray[i]+"original.exe\"\r\n");
					m_file.Write(temp, temp.GetLength());
					temp.Format("call un.Delete_Pe\r\n");
					m_file.Write(temp, temp.GetLength());

					temp.Format("Delete \"$INSTDIR\\"+m_findfile2.m_fileArray[i]+"\"\r\n");
					m_file.Write(temp, temp.GetLength());
				}
				else //�Ϲ� ���� �����
				{
					CString temp;
					temp.Format("Delete \"$INSTDIR\\"+m_findfile2.m_fileArray[i]+"\"\r\n");
					m_file.Write(temp, temp.GetLength());
				}
			}

			//���丮 ����
			SortDirectory();
			
			for(i=1;i<m_DirArray.GetSize();i++)
			{
				CString temp;
				temp.Format("RMDir \"$INSTDIR"+m_DirArray[i]+"\"\r\n");
				m_file.Write(temp, temp.GetLength());
			}
			

		}

		else if(!str.Compare("&"))
		{
			CString temp;
			temp = m_save.m_strSavedir.Right(1);
			if(!temp.Compare("\\"))
			{
				m_file.Write(m_save.m_strSavedir, m_save.m_strSavedir.GetLength());//��ġ���
			}
			else
			{
				m_file.Write(m_save.m_strSavedir, m_save.m_strSavedir.GetLength());//��ġ���
				m_file.Write("\\", sizeof("\\"));
				m_file.Seek(-1, CFile::current);
			}
		}
		else if(!str.Compare("~"))
		{
			m_file.Write(";", sizeof(";"));
			break;
		}

		else
		{
			m_file.Write(&buffer, sizeof(buffer));
		}
	}
	
}

void Sheet::FinishSetup() //������ �ݴ� �Լ�
{
	m_file.Close();
	m_copyfile.Close();
}

void Sheet::CheckStart() //���Ǽ��� ���� �ϴ��� ���ϴ����� ���� ��ư�� ��� ����
{
	if(m_start.m_Bcheck==TRUE)
	{
		this->SetWizardButtons(PSWIZB_NEXT);
	}
	else
	{
		this->SetWizardButtons(NULL);	
	}
}

void Sheet::RunSetup() //������ �� �ʿ���� DATA�� ����� �Լ�
{
	SetCurrentDirectory(m_welcome.Path);
	STARTUPINFO si = {sizeof(STARTUPINFO),};
	PROCESS_INFORMATION pi;
	DWORD ProcID;
	DWORD ExitCode;
	HANDLE hProc;
	CString temp;
	char * path;
	path=new char[MAX_PATH+50];
	CreateProcess(NULL,"makensis.exe Arbiter.nsi", NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
		
	ProcID = pi.dwProcessId;
//	CreateProcessA(NULL,"pause", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcID);
	while(1)
	{
		GetExitCodeProcess(hProc, &ExitCode);
		if(ExitCode!=STILL_ACTIVE)
		{
			TerminateProcess(Loadingpi.hProcess, 0);
			CloseHandle(Loadingpi.hProcess);
			CloseHandle(Loadingpi.hThread);
			temp.Format(m_save.m_strSavedir+"�� "+m_change.m_strSetupName+".exe(SETUP) ������ ��������ϴ�.");
			MessageBox(temp, "Setup Complete", MB_OK);
			break;
		}
	}

	DeleteFile("Arbiter.nsi");
	for(int i=0; i<m_PEarray.GetSize();i++)
	{
		CString str;
		str.Format(m_PEarray[i]);
		DeleteFile(str);
	}
	for(i=0;i<m_OriginalPE.GetSize();i++)
	{
		DeleteFile(m_OriginalPE[i]);
	}
	ProcID = 0;
	CloseHandle(hProc);
}
	

BOOL Sheet::FindEXE(CString str) //pe�� ã�Ƴ��� �Լ�
{
	CString temp;
	int re;
	temp = str.Right(3);
	re = temp.Compare("exe");
	if(re==0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void Sheet::MakePE() //��¥ pe������ ����� �Լ�
{
	for(int i = 0; i<m_PEarray.GetSize();i++)
	{
		CString str;
		CString original;
		str.Format(appPath+"\\"+m_PEarray[i]);
		CopyFileA("DummyProto.exe", str, FALSE);
		original.Format(m_PEarray[i]+"original.exe");
		APR.Abiter_PeCopy(str, original);
	}
}


void Sheet::SetDir() //���丮 ����
{
	m_DirArray.Add("");
	BOOL check;
	for(int i=0; i<m_findfile.m_DirArray.GetSize();i++)
	{
		check = TRUE;
		for(int j=0;j<m_DirArray.GetSize();j++)
		{
			if(!m_findfile.m_DirArray[i].Compare(m_DirArray[j]))//������
			{
				check = FALSE;
			}
		}
		if(check)
		{
			m_DirArray.Add(m_findfile.m_DirArray[i]);
		}
	}
}

//���丮�� ���� �ϴ� �Լ�
void Sheet::SortDirectory()
{
	for(int i=1; i<m_DirArray.GetSize();i++)
	{
		for(int j=i+1;j<m_DirArray.GetSize();j++)
		{
			if(m_DirArray[i].GetLength()<m_DirArray[j].GetLength())
			{
				CString temp;
				temp = m_DirArray[i];
				m_DirArray[i] = m_DirArray[j];
				m_DirArray[j] = temp;
			}
		}
	}

}

void Sheet::MainPECheck()
{
	mainCheck = FALSE;
	for(int i=0;i<m_findfile.m_fileArray.GetSize();i++)
	{
		if(!m_findfile.m_strFileName.Compare(m_findfile.m_fileArray[i]))
		{
			mainCheck = TRUE;
		}
	}	
}