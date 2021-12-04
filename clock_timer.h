//
// Created by johnsalwitz on 11/15/21.
//

#ifndef CLOCK_TIMER_H
#define CLOCK_TIMER_H

void clockTimer_Init();
void clockTimer_Update();
unsigned long clockTimer_GetTime();
unsigned long  clockTimer_GetUpTime();
char *clockTimer_FormatTime(char *buffer);
char *clockTimer_FormatUpTime(char *buffer);
#endif
