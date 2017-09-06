/*============================================================================================
 *
 *  (C) 2010, Phyton
 *
 *  Демонстрационный проект для 1986BE91 testboard
 *
 *  Данное ПО предоставляется "КАК ЕСТЬ", т.е. исключительно как пример, призванный облегчить
 *  пользователям разработку их приложений для процессоров Milandr 1986BE91T1. Компания Phyton
 *  не несет никакой ответственности за возможные последствия использования данного, или
 *  разработанного пользователем на его основе, ПО.
 *
 *--------------------------------------------------------------------------------------------
 *
 *  Файл Menu_gl.с: Функции-обработчики меню - графика
 *
 *============================================================================================*/
#include "Menu.h"
#include "Menu_items.h"
#include "gl.h"
#include "lcd.h"
#include "joystick.h"
#include "systick.h"
#include "text.h"
//#include "mil.c"

/* Служебные функции - рисование графических примитивов */

/* Отрисовка незалитого прямоугольного треугольника */
static void DisplayTriangle (u32 x, u32 y, u32 side) {
    LCD_Line(x, y, x + side, y);
    LCD_Line(x + side, y, x + side, y + side);
    LCD_Line(x, y, x + side, y + side);
}


/* Отрисовка залитого прямоугольного треугольника */
static void DisplayFillingTriangle (u32 x, u32 y, u32 side) {
    u32 i;
    for (i = 0; i < side + 1; i++)
        LCD_Line(x + i, y + i, x + side, y + i);
}


/* Отрисовка круга */
void DisplayFillingCircle (u32 x, u32 y, u32 radius) {
    u32 i;
    for (i = 0; i < radius + 1; i++)
        LCD_Circle(x, y, i);
}


/* Отрисовка незалитого прямоугольника */
void DisplayRectangle (u32 x, u32 y, u32 side_x, u32 side_y) {
    LCD_Line(x, y, x + side_x, y);
    LCD_Line(x, y, x, y + side_y);
    LCD_Line(x + side_x, y, x + side_x, y + side_y);
    LCD_Line(x, y + side_y, x + side_x, y + side_y);
}


/* Отрисовка блока (залитого прямоугольника) */
void DisplayFillingRectangle (u32 x, u32 y, u32 side_x, u32 side_y) {
    u32 i;
    for (i = 0; i < side_y; i++)
        LCD_Line(x, y + i, x + side_x, y + i);
}


/* Функции-обработчики меню */

void ElementsFunc(void) {
#define base_x 25
#define base_y 14
#define side   16

#define offs_x 8
#define offs_y 5

#define circle_radius side / 2
#define circle_x base_x + side + offs_x + circle_radius
#define circle_y base_y + circle_radius
#define circle_filling_y circle_y + circle_radius * 2 + offs_y

#define rectangle_x base_x + side * 2 + offs_x * 2
#define block_y  base_y + side + offs_y

    /* Выводим заголовок */
    LCD_CLS();
    CurrentMethod = MET_OR;
    DisplayMenuTitle("Примитивы");

    /* Строим примитивы и ждем key up */
    DisplayTriangle (base_x, base_y, side);
    DisplayFillingTriangle (base_x, base_y + side + offs_y, side);

    LCD_Circle(circle_x, circle_y, circle_radius);
    DisplayFillingCircle (circle_x, circle_filling_y, circle_radius);

    DisplayRectangle (rectangle_x, base_y, side * 2, side);
    DisplayFillingRectangle (rectangle_x, block_y, side * 2, side);

    WAIT_UNTIL_KEY_RELEASED(SEL);

    /* Ждем нажатия SEL и возвращаемся в главное меню */
    BackToMenuOnSel();
}

void EmblemFunc(void) {
    /* Выводим заголовок */
    u8 str;
    u8 chr;
    u16 let;
static u8 Mil_Data[] = {

                0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x0F,
                0x07,0xC7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,
                0x67,0x27,0x27,0x67,0xE7,0xE7,0xE7,0xE7,
                0x67,0x27,0x27,0x67,0xE7,0xE7,0xC7,0x07,
                0x0F,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xF8,
                0x80,0xC0,0x60,0xC0,0x80,0xF8,0x00,0xF8,
                0x80,0xC0,0x60,0xC0,0x80,0xf8,0x00,0xF8,

                0x60,0x60,0x60,0x60,0x7F,0x7F,0x7F,0x00,
                0x00,0x3F,0x1F,0x8F,0xC7,0xE3,0xF1,0xF8,
                0xFC,0xFE,0xF8,0x00,0x01,0x0F,0x83,0xE0,
                0xF0,0xFC,0xFC,0xC0,0x01,0x0F,0x7F,0x00,
                0x00,0x7F,0x7F,0x7F,0x60,0x60,0x60,0x60,
                0x01,0x00,0xE0,0xE0,0xE1,0xC0,0x80,0x80,
                0xC1,0xE0,0xE0,0xE0,0x01,0x00,0xE0,0xE0,

                0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x00,
                0x00,0x66,0x67,0x67,0x67,0x67,0x67,0x67,
                0x67,0x67,0x67,0x66,0x66,0x67,0x67,0x67,
                0x67,0x67,0x67,0x67,0x66,0x66,0x66,0x60,
                0x00,0x66,0x66,0x66,0x66,0x66,0x66,0x66,
                0x00,0x00,0x7F,0x7F,0x00,0x01,0x07,0x07,
                0x01,0x00,0x7F,0x7F,0x00,0x00,0x7F,0x7F,

                0x00,0x00,0x00,0x00,0xFE,0xFE,0xFE,0xF0,
                0xE0,0xE2,0xE6,0xE6,0xE6,0xE6,0xE6,0xE6,
                0xE6,0xE6,0xE6,0xE6,0xE6,0xE6,0xE6,0xE6,
                0xE6,0xE6,0xE6,0xE6,0xE6,0xE6,0xE2,0xE0,
                0xF0,0xFE,0xFE,0xFE,0x00,0x00,0x00,0x00,
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

//************************************************************************

                0x80,0xC0,0x60,0xC0,0x80,0xF8,0x00,0x00,
                0x00,0xF8,0x30,0x60,0x30,0xF8,0x00,0xF8,
                0x00,0xF8,0x00,0x00,0x00,0x00,0xE0,0xB8,
                0x88,0xB8,0xE0,0x00,0xF8,0x30,0x60,0xC0,
                0xF8,0x00,0xF8,0x08,0x98,0xF0,0x00,0xF8,
                0x48,0xC8,0xB0,0x00,0x00,0x00,0xF8,0x48,
                0xC8,0xB0,0x00,0xF8,0x80,0x00,0x00,0xF8,

                0x01,0x00,0x80,0xC0,0xE1,0xE0,0x00,0x01,
                0x00,0x81,0xC0,0xE0,0x60,0x61,0xE0,0xE1,
                0x00,0x01,0x01,0x01,0xC1,0xE0,0xE1,0xC0,
                0x00,0x00,0x01,0x00,0xE1,0xE0,0x00,0x00,
                0x01,0x00,0xE1,0xE1,0x01,0x00,0x00,0x01,
                0x80,0xC0,0xE1,0xE0,0xE1,0xE0,0x01,0x00,
                0x00,0xE1,0xE0,0x60,0x61,0xE1,0xC1,0x81,

                0x0E,0x07,0x03,0x01,0x7F,0x7F,0x00,0x00,
                0x7F,0x7F,0x01,0x00,0x00,0x00,0x7F,0x7F,
                0x00,0x00,0x78,0x7F,0x07,0x31,0x31,0x3F,
                0x7F,0x78,0x00,0x00,0x7F,0x7F,0x00,0x06,
                0x06,0x06,0x7F,0x7F,0x00,0x00,0x60,0x6F,
                0x6F,0x63,0x60,0x60,0x7F,0x7F,0x60,0x00,
                0x00,0x7F,0x7F,0x00,0x0C,0x0E,0x07,0x03



};
static uc8 STR[4][76] = { "Отладочная плата для микроконтроллера 1986ВЕ92У. Новая серия 32-х разрядных ",
                          "микроконтроллеров на базе ядра ARM Cortex-M3. Объем Flash память 128 Кбайт. ",
                          "Объем ОЗУ 32 Кбайт. Широкий набор интерфейсов: CAN, UART, SPI, USB и другие ",
                          "Аналоговые блоки 12-ти битных АЦП и ЦАП, схема компаратора и многое другое! "};


    FONT *OldFont = CurrentFont;

    LCD_CLS();
//    CurrentMethod = MET_OR;
//    DisplayMenuTitle("ЗАО 'ПКК Миландр'");
    WAIT_UNTIL_KEY_RELEASED(SEL);
    let = 0;
    SetCrystal(0);
    for (str=1;str<5;str++)
        {
        LCD_SET_PAGE(str);
        for (chr=8;chr<64;chr++)
                {
                LCD_SET_ADDRESS(chr);
                WriteLCD_Data(Mil_Data[let++]);
                }
        }
    SetCrystal(1);
    for (str=1;str<4;str++)
        {
        LCD_SET_PAGE(str);
        for (chr=0;chr<56;chr++)
                {
                LCD_SET_ADDRESS(chr);
                WriteLCD_Data(Mil_Data[let++]);
                }
        }
    /* Ждем нажатия SEL и возвращаемся в главное меню */
    CurrentMethod = MET_AND;
    CurrentFont = &Font_7x10_bold;
    let=0;
    while ( !KEY_PRESSED(SEL))
    {
    if (let>304) let =0;
    LCD_PUTC(0,48,' ');
    LCD_PUTSL(6, 48, &STR[0][let],18);
    SysTickDelay(500);
    LCD_PUTSL(5, 48, &STR[0][let],18);
    SysTickDelay(500);
    LCD_PUTSL(4, 48, &STR[0][let],18);
    SysTickDelay(500);
    LCD_PUTSL(3, 48, &STR[0][let],18);
    SysTickDelay(500);
    LCD_PUTSL(2, 48, &STR[0][let],18);
    SysTickDelay(500);
    LCD_PUTSL(1, 48, &STR[0][let],18);
    SysTickDelay(500);
    LCD_PUTSL(0, 48, &STR[0][let++],18);
    SysTickDelay(500);

    };
    CurrentFont = OldFont;
    DisplayMenu();
}


void IndicatorsFunc(void) {
#define side_x 4

    s32 i, sign;

    /* Выводим заголовок и ждем key up */
    LCD_CLS();
    CurrentMethod = MET_OR;
    DisplayMenuTitle("Индикаторы");
    WAIT_UNTIL_KEY_RELEASED(SEL);

    /* Выводим progress bar */
    LCD_PUTS(24,18,"0");
    DisplayRectangle (32, 14, 64, 14);
    LCD_PUTS(97,18,"100");
    /* Выводим шкалу */
    LCD_Circle(63, 63, 30);
    LCD_Line(63, 34, 63, 41);
    LCD_Line(35, 53, 42, 56);
    LCD_Line(91, 53, 84, 56);
    LCD_Line(45, 39, 51, 45);
    LCD_Line(81, 39, 75, 45);

    /* Эмулируем прогресс - от 0 до 100% и обратно */
    /* Эмулируем дрожание стрелки шкалы            */
    CurrentMethod = MET_XOR;
    for (i = 0, sign = 1; !KEY_PRESSED(SEL); ) {
        s32 ni = i + side_x * sign;
        DisplayFillingRectangle (i + 34, 16, side_x - 1, 11);
        if (ni > 60 || ni < 0)
            sign = -sign;
        else
            i = ni;
        SysTickDelay(300);

        /* Рисуем стрелку */
        LCD_Line(86, 46, 63, 63);
        SysTickDelay(150);
        LCD_Line(86, 46, 63, 63);
        SysTickDelay(150);
        LCD_Line(84, 44, 63, 63);
        SysTickDelay(150);
        LCD_Line(84, 44, 63, 63);
        SysTickDelay(150);
    }

    /* Нажата SEL - возвращаемся в главное меню */
    DisplayMenu();
}

u32    ToGregorData(u32 SecondQn,u8 Sel)
{
    u32 d = SecondQn / 86400 + 2451544;
    u32 Z = d+1;
    u32 A = Z;
    if( Z >= 2299161 )
    {
        u32 Alpha = ((Z*4-7468865) / 146097);
        A = Z + 1 + Alpha - Alpha/4;
    }

    {
        u32 B = A + 1524;
        u32 C = (B*40 - 4884) / 14610;
        u32 D = (1461 * C)/4;
        u32 E = ((B - D)*10000/306001);
        u32 Day = B - D - (306001 * E)/10000;

        u32 Month = E - 13;
        u32 Year = C - 4715;

        if( E < 14 )
            Month = E - 1;

        if( Month > 2 )
            Year = C - 4716;
		if (Sel==1) return Day%100;
		else if (Sel==2) return Month%100;
		else if (Sel==3) return Year%100;
		else return (Day%100)*10000+(Month%100)*100+Year%100;

    }
}


void RTC_INIT(void)
{

//PORTD->ANALOG = 0x3<<10;
//PORTD->PWR    = 0xF<<20;
//PORTD->RXTX   = 0x0<<10;
//PORTD->OE     = 0x3<<10;
	RST_CLK->PER_CLOCK=0xFFFFFFFF;
	POWER->PVDCS = 0x01;
	BKP->REG_0F |=0x40000000;
	while(1){}; 

if (~BKP->REG_0F && 0x15)
{
BKP->REG_0F &= ~(1<<0);	 //Stop LSE 
BKP->REG_0F &= ~(1<<4);	 //Stop clock for re/initialization 
BKP->REG_0F &= ~(0xFF<<5); // Clear Callibration


//PORTD->RXTX = 1<<10;
BKP->REG_0F |= 1 | 1<<2;  // Enable LSE
while ((BKP->REG_0F & 1<<13)==0x00) {};
//PORTD->RXTX = 3<<10;
BKP->RTC_PRL = 32768;    // Set second base
while (BKP->RTC_CS & 0x40) {};  // wait while set

BKP->REG_0F |= 1<<4;// | 1<<2 ;//| 1<<5; // Enable RTC
}
}

void ClockFunc(void) {
    /* Выводим заголовок */
	u32 temp;
	u32 Sec;
	u32 Min;
	u32 Clck;
	u8 i;
	u8 S1[8];
	u8 V;
	FONT *OldFont = CurrentFont;
	RTC_INIT();
    LCD_CLS();

	POWER->PVDCS = 1;
	CurrentMethod = MET_FIX;
    WAIT_UNTIL_KEY_RELEASED(SEL);
    DisplayMenuTitle("Дата и время");
    CurrentMethod = MET_FIX;


    while ( !KEY_PRESSED(SEL))
    {

	V=0;
	for (i=0;i<4;i++)
	{	
	POWER->PVDCS = 1 | i<<1;
	POWER->PVDCS &=~(0x03<<6);
	if ((i==3) && (POWER->PVDCS&0x040)) V=4;
	else if ((i==2) && (POWER->PVDCS&0x040)) V=3;
	else if ((i==1) && (POWER->PVDCS&0x040)) V=2;
	else if ((i==0) && (POWER->PVDCS&0x040)) V=1;
	POWER->PVDCS =0;
	}
	     if(V==0) LCD_PUTSL(8,40,"BUcc=[0.0...1.8]V",17);	
	else if(V==1) LCD_PUTSL(8,40,"BUcc=[1.9...2.2]V",17);	
	else if(V==2) LCD_PUTSL(8,40,"BUcc=[2.3...2.6]V",17);	
	else if(V==3) LCD_PUTSL(8,40,"BUcc=[2.7...3.0]V",17);	
	else if(V==4) LCD_PUTSL(8,40,"BUcc=[3.1...3.6]V",17);	

	V=0;
	for (i=0;i<8;i++)
	{	
	POWER->PVDCS = 1 | i<<3;
	POWER->PVDCS &=~(0x03<<6);
		 if ((i==7) && (POWER->PVDCS&0x080)) V=8;
	else if ((i==6) && (POWER->PVDCS&0x080)) V=7;
	else if ((i==5) && (POWER->PVDCS&0x080)) V=6;
	else if ((i==4) && (POWER->PVDCS&0x080)) V=5;
	else if ((i==3) && (POWER->PVDCS&0x080)) V=4;
	else if ((i==2) && (POWER->PVDCS&0x080)) V=3;
	else if ((i==1) && (POWER->PVDCS&0x080)) V=2;
	else if ((i==0) && (POWER->PVDCS&0x080)) V=1;
	POWER->PVDCS =0;
	}
	     if(V==0) LCD_PUTSL(8,48," Ucc=[0.0...2.0]V",17);	
	else if(V==1) LCD_PUTSL(8,48," Ucc=[2.1...2.2]V",17);	
	else if(V==2) LCD_PUTSL(8,48," Ucc=[2.3...2.4]V",17);	
	else if(V==3) LCD_PUTSL(8,48," Ucc=[2.5...2.6]V",17);	
	else if(V==4) LCD_PUTSL(8,48," Ucc=[2.7...2.8]V",17);	
	else if(V==5) LCD_PUTSL(8,48," Ucc=[2.9...3.0]V",17);	
	else if(V==6) LCD_PUTSL(8,48," Ucc=[3.1...3.2]V",17);	
	else if(V==7) LCD_PUTSL(8,48," Ucc=[3.3...3.4]V",17);	
	else if(V==8) LCD_PUTSL(8,48," Ucc=[3.5...3.6]V",17);	

	temp = BKP->RTC_CNT;
	 
	Sec = temp%60;
	Min = (temp/60)%60;
	Clck = ((temp/60)/60)%24;

	S1[0] = Clck/10+0x30;
	S1[1] = Clck%10+0x30;
	S1[2] = ':';
	S1[3] = Min/10+0x30;
	S1[4] = Min%10+0x30;
	S1[5] = ':';
	S1[6] = Sec/10+0x30;
	S1[7] = Sec%10+0x30;
	LCD_PUTSL(8,16,S1,8);
	S1[0] = ToGregorData(temp,1)/10+0x30;
	S1[1] = ToGregorData(temp,1)%10+0x30;
	S1[2] = '/';
	S1[3] = ToGregorData(temp,2)/10+0x30;
	S1[4] = ToGregorData(temp,2)%10+0x30;
	S1[5] = '/';
	S1[6] = ToGregorData(temp,3)/10+0x30;
	S1[7] = ToGregorData(temp,3)%10+0x30;
	LCD_PUTSL(8,24,S1,8);

	
    };
    CurrentFont = OldFont;
    DisplayMenu();
}

/*============================================================================================
 * Конец файла Menu_gl.с
 *============================================================================================*/

