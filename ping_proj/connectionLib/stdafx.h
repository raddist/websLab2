// stdafx.h: ���������� ���� ��� ����������� ��������� ���������� ������
// ��� ���������� ������ ��� ����������� �������, ������� ����� ������������, ��
// �� ����� ����������
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ��������� ����� ������������ ���������� �� ���������� Windows
// ����� ���������� Windows:
#pragma once

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

#include "targetver.h"

#include <stdio.h>
#include <cstdlib>
#include <tchar.h>
#include <winsock2.h>
#include <windows.h>
#include <Ws2tcpip.h>

#include <sstream>
#include <string.h>
