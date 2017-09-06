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
 *  ���� Menu_text.c: �������-����������� ���� - ����� ������
 *
 *============================================================================================*/

#include <string.h>

#include "lcd.h"
#include "Menu.h"
#include "Menu_items.h"
#include "text.h"
#include "joystick.h"


void FontFunc(void) {
    FONT *OldFont = CurrentFont;

    /* ������� ��������� � ���� key up */
    LCD_CLS();
    CurrentMethod = MET_AND;
    CurrentFont = &Font_6x8;
    DisplayMenuTitle("������� �������");
    WAIT_UNTIL_KEY_RELEASED(SEL);

    /* ������� ������� */
    LCD_PUTS(0, 12, "�����6X8");

    CurrentFont = &Font_12x16;
    LCD_PUTS(0, 22, "�����12X16");

    CurrentFont = &Font_7x10_thin;
    LCD_PUTS(0, 40, "�����7X10");

    CurrentFont = &Font_7x10_bold;
    LCD_PUTS(0, 52, "�����7X10 ������");

    /* ���� ������� SEL � ������������ � ������� ���� */
    CurrentFont = OldFont;
    BackToMenuOnSel();
}


void StyleFunc(void) {
    FONT *OldFont = CurrentFont;

    /* ������� ��������� � ���� key up */
    LCD_CLS();
    CurrentMethod = MET_AND;
    CurrentFont = &Font_6x8;
    DisplayMenuTitle("������� ������");
    WAIT_UNTIL_KEY_RELEASED(SEL);

    /* ������� ������ */
    do {
        LCD_PUTS_Ex(0, 12, "���������", StyleBlink);
        if (KEY_PRESSED(SEL)) break;
        LCD_PUTS_Ex(0, 32, "����������", StyleFlipFlop);
        if (KEY_PRESSED(SEL)) break;
        LCD_PUTS_Ex(0, 52, "��������", StyleVibratory);
    } while (!KEY_PRESSED(SEL));

    /* ������ SEL - ������������ � ������� ���� */
    CurrentFont = OldFont;
    DisplayMenu();
}


void ShiftFunc(void) {
    FONT *OldFont = CurrentFont;

    /* ������� ��������� � ���� key up */
    LCD_CLS();
    CurrentMethod = MET_AND;
    CurrentFont = &Font_6x8;
    DisplayMenuTitle("������� ������");
    WAIT_UNTIL_KEY_RELEASED(SEL);

    /* TODO - ������� ������ */
    do {

    } while (!KEY_PRESSED(SEL));

    /* ������ SEL - ������������ � ������� ���� */
    CurrentFont = OldFont;
    DisplayMenu();
}

/* ����� ��� ������������ "����������� �����" */
static char Book[16][22] = {
        {"���������������� ��- "},
        {"��� 1986��91 ��������"},
        {"������������������ ��"},
        {"���������� Flash ��- "},
        {"����� �������� �     "},
        {"��������� �� ����    "},
        {"�������������������- "},
        {"���� �������������   "},
        {"RISC ���� Cortex-M3. "},
        {"��������������� ����-"},
        {"���� �� �������� ���-"},
        {"���� �� 80 ��� � ��- "},
        {"������ 128 �� Flash  "},
        {"������ �������� � 32 "},
        {"�� ���.              "}
};

void BookFunc(void){
    u32 top_ind, key, i;

    /* ������� ����� � ���� key up */
    LCD_CLS();
    CurrentMethod = MET_AND;
    WAIT_UNTIL_KEY_RELEASED(SEL);

    /* ���� ��������� ������� ������ */
    for (top_ind = 0, key = NOKEY; key != SEL; ){
        /* ������� ����� � ���� ������� ������ */
        for (i = 0; i < 8; i++)
            LCD_PUTS(0, (CurrentFont->Height) * i, Book[top_ind + i]);
        WAIT_UNTIL_ANY_KEY;

        /* ��������� ������� ������ */
        key = GetKey();
        switch (key) {
            /* �������������� ����� */
            case UP:
                if (top_ind > 0)
                    top_ind--;
                break;
            /* �������������� ���� */
            case DOWN:
                if (top_ind < 7)
                    top_ind++;
                break;
    }
  }

  /* ������ SEL - ������������ � ������� ���� */
  WAIT_UNTIL_KEY_RELEASED(key);
  DisplayMenu();
}


void AboutFunc(void) {

    /* ������� ����� About */
    LCD_CLS();
    CurrentMethod = MET_AND;

    LCD_PUTS(0, 0, " Milandr 1986BE91T1 ");
    LCD_PUTS(0, CurrentFont->Height + 1, "   Testing-board    ");
    LCD_PUTS(0, (CurrentFont->Height) * 2 + 2, "                    ");
    LCD_PUTS(0, (CurrentFont->Height) * 3 + 2, "                    ");
    LCD_PUTS(0, (CurrentFont->Height) * 4 + 3, "Appl. example v.1.0 ");
    LCD_PUTS(0, (CurrentFont->Height) * 5 + 4, "    Phyton 2010     ");
    LCD_PUTS(0, (CurrentFont->Height) * 6 + 5, "   www.phyton.ru    ");

    /* ���� ������� SEL � ������������ � ������� ���� */
    BackToMenuOnSel();
}

/*============================================================================================
 * ����� ����� Menu_text.c
 *============================================================================================*/

