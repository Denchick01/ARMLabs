/*============================================================================================
 *
 *  (C) 2010, Phyton
 *
 *  ���������������� ������ ��� 1986BE91 testboard
 *
 *  ������ �� ��������������� "��� ����", �.�. ������������� ��� ������, ���������� ���������
 *  ������������� ���������� �� ���������� ��� ����������� Milandr 1986BE91T1. �������� Phyton
 *  �� ����� ������� ��������������� �� ��������� ����������� ������������� �������, ���
 *  �������������� ������������� �� ��� ������, ��.
 *
 *--------------------------------------------------------------------------------------------
 *
 *  ���� joystick.c: ������ � ������� ������ ("����������")
 *
 *============================================================================================*/

#include "joystick.h"

/* ����� � ������������ "����� ������" */

#define No_Key_Pressed      0x7C00

static uc32 KeyMasks[NUM_KEY_CODES] = {
        No_Key_Pressed, /* NOKEY    */
        0x7800,         /* SEL      */
        0x3C00,         /* RIGHT    */
        0x5C00,         /* LEFT     */
        0x7400,         /* UP       */
        0x6C00          /* DOWN     */
};

/* ����������� "����" �� ������� ������� */
KeyCode GetKey(void) {
    u32 i, j, data;

    data = PORTC->RXTX;

    if ((data & No_Key_Pressed) == No_Key_Pressed)
      return NOKEY;

    for (i = 1; i < NUM_KEY_CODES; i++) {
        for (j = 0; ((data & No_Key_Pressed) == KeyMasks[i]) && (j < 16); j++);
        if (j > 0)
            return j > 15 ? ((KeyCode)i) : NOKEY;
    }

    return MULTIPLE;
}

/*============================================================================================
 * ����� ����� joystick.c
 *============================================================================================*/
