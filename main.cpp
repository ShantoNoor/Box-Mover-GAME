#include "BGI/graphics.h"
#include <stdio.h>
#include <windows.h>
//#include <cstdlib>
#include <ctime>

int main()
{
    Beep(5000, 100);

    DWORD sW = GetSystemMetrics(SM_CXSCREEN);
    DWORD sH = GetSystemMetrics(SM_CYSCREEN);

    int gW = 1024, gH = 576, window1, window2;

    window1 = initwindow(gW, gH, "Box Mover GAME", (sW-gW)/2, (sH-gH)/2);
    setcurrentwindow(window1);

    //For random number generator
    srand(time(0));

    int i, j, tW, tH, page = 0, page1, x = 10, s, score = 0, highscore, check;
    j = -gH;

    //car co-ordinates
    int cmx = (gW/2 + gW/3)/2 + 56;
    int cmy = gH-120;

    //for enemy car 1
    int ex, es, ec, et;
    //for enemy car 2
    int ex1, ec1, et1;

    //button delay
    int bd = 900;

    //animation
    int co = 10;

    //color
    int color = 1;

    //Credit & FullScreen on off checker;
    int fc = 0;
    int cc = 0;

    //File for high score-->
    FILE *HS;
    HS = fopen("score.txt", "r");

    if(HS == NULL)
    {
        highscore = 0;
    }
    else
    {
        fscanf(HS, "%d", &highscore);
        fclose(HS);
    }

    //FIRST/END Screen--->
    FIRST_SCREEN:
        while(1)
        {
            setactivepage(page);
            setvisualpage(1-page);

            cleardevice();

            setfillstyle(SOLID_FILL, LIGHTGREEN);
            bar(0, 0, gW, gH);

            setfillstyle(SOLID_FILL, DARKGRAY); //8
            bar(gW/3, 0, gW*2/3, gH);

            //Text--->
            setcolor(WHITE);
            settextstyle(8, HORIZ_DIR, 15);

            //Start text
            char startText[6] = "Start";
            tW = textwidth(startText);
            tH = textheight(startText);
            setfillstyle(SOLID_FILL, WHITE);
            bar(gW/6-tW/2 - 4, (gH/2-tH/2)-tH/2 - 8, gW/6-tW/2 + 104, (gH/2-tH/2)-tH/2 + 30);
            outtextxy(gW/6-tW/2, (gH/2-tH/2)-tH/2-5, startText);

            //Exit text
            char exitText[5] = "Exit";
            tW = textwidth(exitText);
            tH = textheight(exitText);
            setfillstyle(SOLID_FILL, WHITE);
            bar(gW/6-tW/2 - 4, ((gH/2-tH/2)+tH/2) +2, gW/6-tW/2 + 84, ((gH/2-tH/2)+tH/2) + 40);
            outtextxy(gW/6-tW/2, (gH/2-tH/2)+tH/2+5, exitText);

            //High Score text
            char highscoreText[20];
            sprintf(highscoreText, "Best Score:%d", highscore);
            tW = textwidth(highscoreText);
            tH = textheight(highscoreText);
            outtextxy((gW+(gW*2)/3)/2 - tW/2, (gH/2-tH/2), highscoreText);
        //Text---<

        //Road--->
            //Side_line
            setfillstyle(SOLID_FILL, WHITE);
            bar((gW/3)-5, 0, (gW/3)+5, gH);
            bar((gW*2/3)-5, 0, (gW*2/3)+5, gH);

            //middle lines
            for(i = 0; i <= gH; i += 40)
            {
                //Middle Border
                setfillstyle(SOLID_FILL, WHITE);
                bar((gW/2)-5, i+j, (gW/2)+5, i+25+j);
            }
            j += x;
            if(j > gH)
                j = -gH;

            //Road---<

            //My Car---->
            setfillstyle(SOLID_FILL, LIGHTRED);
            bar(cmx, cmy, cmx+60, cmy+80);

            if(GetAsyncKeyState(VK_LEFT) && cmx >= gW/3+10)
            {
                cmx -= x;
            }
            else if(GetAsyncKeyState(VK_RIGHT) && cmx+60 <= gW*2/3-10)
            {
                cmx += x;
            }
            else if(GetAsyncKeyState(VK_UP) && cmy >= 0)
            {
                cmy -= x;
            }
            else if(GetAsyncKeyState(VK_DOWN) && cmy+80 <= gH)
            {
                cmy += x;
            }
            //My Car----<

            //help text
            setcolor(LIGHTRED);
            settextstyle(8, HORIZ_DIR, 15);
            char helpText1[10] = "Use The";
            char helpText2[15] = "AERROW Keys";
            char helpText3[20] = "To Move The Box";

            tW = textwidth(helpText1);
            tH = textheight(helpText1);
            outtextxy((gW-tW)/2, 30, helpText1);

            tW = textwidth(helpText2);
            tH = textheight(helpText2);
            outtextxy((gW-tW)/2, 65, helpText2);

            tW = textwidth(helpText3);
            tH = textheight(helpText3);
            outtextxy((gW-tW)/2, 100, helpText3);

            if(co <= 3)
            {
                //Starting text
                char StartingText[20];
                sprintf(StartingText, "Starting In %d", co);
                tW = textwidth(StartingText);
                tH = textheight(StartingText);
                outtextxy((gW-tW)/2, (gH-tH)/2, StartingText);
                delay(500);
                if(co == 0)
                    goto START;
                co--;
            }


            //Start Button
            tW = textwidth(startText);
            tH = textheight(startText);
            if((mousex() >= (gW/6-tW/2 - 4)) && (mousex() <= (gW/6-tW/2 + 104)) && (mousey() >= ((gH/2-tH/2)-tH/2 - 8)) && (mousey() <= ((gH/2-tH/2)-tH/2 + 30)))
            {
                setfillstyle(SOLID_FILL, LIGHTBLUE);
                bar(gW/6-tW/2 - 4, (gH/2-tH/2)-tH/2 - 8, gW/6-tW/2 + 104, (gH/2-tH/2)-tH/2 + 30);
                setcolor(LIGHTBLUE);
                outtextxy(gW/6-tW/2, (gH/2-tH/2)-tH/2-5, startText);
            }

            if((mousex() >= (gW/6-tW/2 - 4)) && (mousex() <= (gW/6-tW/2 + 104)) && (mousey() >= ((gH/2-tH/2)-tH/2 - 8)) && (mousey() <= ((gH/2-tH/2)-tH/2 + 30)) && GetAsyncKeyState(VK_LBUTTON))
            {
                cc = 0;
                Beep(4000,100);
                co = 3;
            }
            //start button

            // exit Button
            tW = textwidth(exitText);
            tH = textheight(exitText);
            if((mousex() >= ( gW/6-tW/2 - 4 )) && (mousex() <= ( gW/6-tW/2 + 84 )) && (mousey() >= ( ((gH/2-tH/2)+tH/2) +2 )) && (mousey() <= ( ((gH/2-tH/2)+tH/2) + 40 )))
            {
                setfillstyle(SOLID_FILL, LIGHTBLUE);
                bar(gW/6-tW/2 - 4, ((gH/2-tH/2)+tH/2) +2, gW/6-tW/2 + 84, ((gH/2-tH/2)+tH/2) + 40);
                setcolor(LIGHTBLUE);
                outtextxy(gW/6-tW/2, (gH/2-tH/2)+tH/2+5, exitText);
            }
            if((mousex() >= ( gW/6-tW/2 - 4 )) && (mousex() <= ( gW/6-tW/2 + 84 )) && (mousey() >= ( ((gH/2-tH/2)+tH/2) +2 )) && (mousey() <= ( ((gH/2-tH/2)+tH/2) + 40 )) && GetAsyncKeyState(VK_LBUTTON))
            {
                Beep(4000,100);
                delay(bd);
                goto END;
            }
            // exit Button

            //Full Screen Box Buttorn
            //Big box
            setfillstyle(SOLID_FILL, WHITE);
            bar(gW-49, gH-49, gW-11, gH-9);
            //small box
            setfillstyle(SOLID_FILL, LIGHTBLUE);
            if(fc == 0)
                bar(gW-30, gH-30, gW-15, gH-13);
            if(fc == 1)
                bar(gW-45, gH-45, gW-30, gH-28);

            //Exit screen button on
            if((mousex() >= ( gW-49 )) && (mousex() <= ( gW-11 )) && (mousey() >= ( gH-49 )) && (mousey() <= ( gH-9 )) && fc == 0)
            {
                //big box
                setfillstyle(SOLID_FILL, LIGHTBLUE);
                bar(gW-49, gH-49, gW-11, gH-9);
                //Middel box
                setfillstyle(SOLID_FILL, WHITE);
                bar(gW-45, gH-45, gW-15, gH-13);
            }
            //Full Screen Button off
            if((mousex() >= ( gW-49 )) && (mousex() <= ( gW-11 )) && (mousey() >= ( gH-49 )) && (mousey() <= ( gH-9 )) && fc == 1)
            {
                //big box
                setfillstyle(SOLID_FILL, LIGHTBLUE);
                bar(gW-49, gH-49, gW-11, gH-9);
                //Middel box
                setfillstyle(SOLID_FILL, WHITE);
                bar(gW-45, gH-45, gW-15, gH-13);
                //Small box
                setfillstyle(SOLID_FILL, LIGHTBLUE);
                bar(gW-30, gH-30, gW-15, gH-13);
            }
            //Full Screen Exit Logic
            //Full Screen Box Button Logic
            if((mousex() >= ( gW-49 )) && (mousex() <= ( gW-11 )) && (mousey() >= ( gH-49 )) && (mousey() <= ( gH-9 )) && GetAsyncKeyState(VK_LBUTTON) && fc == 0)
            {
                fc = 1;
                Beep(4000, 100);
                gW = sW;
                gH = sH;
                cmx = cmx + 171;
                cmy = cmy + 190;
                window2 = initwindow(gW, gH, "", -3, -3);
                closegraph(window1);
                delay(100);
                setcurrentwindow(window2);
            }
            //Full Screen Box Button Logic
            //Full Screen Exit Logic
            if((mousex() >= ( gW-49 )) && (mousex() <= ( gW-11 )) && (mousey() >= ( gH-49 )) && (mousey() <= ( gH-9 )) && GetAsyncKeyState(VK_LBUTTON) && fc == 1)
            {
                fc = 0;
                Beep(4000, 100);
                gW = 1024;
                gH = 576;
                cmx = cmx - 171;
                cmy = cmy - 190;
                window1 = initwindow(gW, gH, "Box Mover GAME", (sW-gW)/2, (sH-gH)/2);
                closegraph(window2);
                delay(100);
                setcurrentwindow(window1);
            }
            //Full Screen Exit Logic

            //Start Credit Button
            //Credit--->
            char creditText[7] = "Credit";
            tW = textwidth(creditText);
            tH = textheight(creditText);
            setfillstyle(SOLID_FILL, WHITE);
            setcolor(WHITE);
            if(cc == 1)
            {
                setfillstyle(SOLID_FILL, LIGHTBLUE);
                setcolor(LIGHTBLUE);
            }
            bar(gW-tW-60-5, gH-45-4, gW-55, gH-9);
            outtextxy(gW-tW-60, gH-45, creditText);

            //Credit Text
            if(cc == 1)
            {
                setcolor(LIGHTBLUE);
                char nameText[20] = "Md Noor E Musa";
                tW = textwidth(nameText);
                tH = textheight(nameText);
                outtextxy((gW-tW)/2, (gH-tH)/2, nameText);
                char idText[15] = "ID:18CSE033";
                tW = textwidth(idText);
                tH = textheight(idText);
                outtextxy((gW-tW)/2, (gH-tH)/2+35, idText);
            }

            //Credit Button
            tW = textwidth(creditText);
            tH = textheight(creditText);
            if((mousex() >= ( gW-tW-60-5 )) && (mousex() <= ( gW-55 )) && (mousey() >= ( gH-45-4 )) && (mousey() <= ( gH-9 )) && cc==0)
            {
                setfillstyle(SOLID_FILL, LIGHTBLUE);
                bar(gW-tW-60-5, gH-45-4, gW-55, gH-9);
                setcolor(LIGHTBLUE);
                outtextxy(gW-tW-60, gH-45, creditText);
            }
            //Credit on
            if((mousex() >= ( gW-tW-60-5 )) && (mousex() <= ( gW-55 )) && (mousey() >= ( gH-45-4 )) && (mousey() <= ( gH-9 )) && GetAsyncKeyState(VK_LBUTTON) && cc == 0)
            {
                Beep(4000, 100);
                delay(bd);
                cc = 1;
            }
            //Credit off
            if((mousex() >= ( gW-tW-60-5 )) && (mousex() <= ( gW-55 )) && (mousey() >= ( gH-45-4 )) && (mousey() <= ( gH-9 )) && cc == 1)
            {
                setfillstyle(SOLID_FILL, WHITE);
                bar(gW-tW-60-5, gH-45-4, gW-55, gH-9);
                setcolor(WHITE);
                outtextxy(gW-tW-60, gH-45, creditText);
            }
            //Credit off
            if((mousex() >= ( gW-tW-60-5 )) && (mousex() <= ( gW-55 )) && (mousey() >= ( gH-45-4 )) && (mousey() <= ( gH-9 )) && GetAsyncKeyState(VK_LBUTTON) && cc == 1)
            {
                Beep(4000, 100);
                delay(bd);
                cc = 0;
            }
            //End of Credit Button

            page = 1-page;
            delay(20);
        }

    START:
    //Code--->
        page = 0, s = 0, x = 10, es=0;
        et=et1=0;
        cmx = (gW/2 + gW/3)/2 + 56;
        cmy = gH-120;
        co = 10;
        score = 0;
        check = 0;
        cc = 0;

        while(1)
        {
            setactivepage(page);
            setvisualpage(1-page);

            cleardevice();

            score++;

            setfillstyle(SOLID_FILL, LIGHTGREEN);
            bar(0, 0, gW, gH);

            setfillstyle(SOLID_FILL, DARKGRAY); //8
            bar(gW/3, 0, gW*2/3, gH);

            //Text--->
                settextstyle(8, HORIZ_DIR, 15);
                setcolor(WHITE);

                //END text
                char endText[4] = "End";
                tW = textwidth(endText);
                tH = textheight(endText);
                setfillstyle(SOLID_FILL, WHITE);
                bar(gW/6-tW/2 - 4, (gH/2-tH/2)-tH/2 - 8, gW/6-tW/2 + 64, (gH/2-tH/2)-tH/2 + 30);
                outtextxy(gW/6-tW/2, (gH/2-tH/2)-tH/2-5, endText);

                //Exit text
                char exitText[5] = "Exit";
                tW = textwidth(exitText);
                tH = textheight(exitText);
                setfillstyle(SOLID_FILL, WHITE);
                bar(gW/6-tW/2 - 4, ((gH/2-tH/2)+tH/2) +2, gW/6-tW/2 + 84, ((gH/2-tH/2)+tH/2) + 40);
                outtextxy(gW/6-tW/2, (gH/2-tH/2)+tH/2+5, exitText);

                //High Score text
                char highscoreText[20];
                sprintf(highscoreText, "Best Score:%d", highscore);
                tW = textwidth(highscoreText);
                tH = textheight(highscoreText);
                outtextxy((gW+(gW*2)/3)/2 - tW/2, (gH/2-tH/2)-tH/2-5, highscoreText);

                //Score text
                char scoreText[20];
                sprintf(scoreText, "Score:%d", score);
                tW = textwidth(scoreText);
                tH = textheight(scoreText);
                outtextxy((gW+(gW*2)/3)/2 - tW/2, (gH/2-tH/2)+tH/2+5, scoreText);


            //Text---<

            //Road--->
                //Side_line
                setfillstyle(SOLID_FILL, WHITE);
                bar((gW/3)-5, 0, (gW/3)+5, gH);
                bar((gW*2/3)-5, 0, (gW*2/3)+5, gH);

                //middle lines
                for(i = 0; i <= gH; i += 40)
                {
                    //Middle Border
                    setfillstyle(SOLID_FILL, WHITE);
                    bar((gW/2)-5, i+j, (gW/2)+5, i+25+j);
                }
                if(fc == 0)
                    j += x;
                else if(fc == 1)
                    j += x+4;
                if(j > gH)
                    j = -gH;

            //Road---<

            //Enemy Car--->
            //CAR--> //gW = 1024, gH = 576;
            //Left side -> (gW/3)+7 = 347
            //Right side -> (gW*2/3)-7 = 675
            // Difference -> R-L = 675-347 = 328
            // 328 - 71 = 257
                if(et == 0)
                {
                    ex = ((gW/3)+6)+(rand()%((gW*2/3)-(gW/3)-79));
                    ec = (rand()%15);
                    if(ec == 8 || ec == 12)
                        ec--;
                    et = 1;
                    setfillstyle(SOLID_FILL, ec);
                    bar(ex, 0, ex+71, -100);
                }
            //CAR-->
            //CAR 1-->
                if(et1 == 0)
                {
                    ex1 = ((gW/3)+6)+(rand()%((gW*2/3)-(gW/3)-79));
                    while((ex1 >= ex && ex1 <= ex+71) || (ex1+71 >= ex && ex1+71 <= ex+71))
                    {
                        ex1 = ((gW/3)+6)+(rand()%((gW*2/3)-(gW/3)-79));
                    }
                    ec1 = (rand()%15);

                    if(ec1 == 8 || ec1 == 12)
                        ec1++;
                    et1 = 1;
                    setfillstyle(SOLID_FILL, ec1);
                    bar(ex1, 0, ex1+71, -100);
                }

                setfillstyle(SOLID_FILL, ec);
                bar(ex, 0+es, ex+71, -100+es);

                setfillstyle(SOLID_FILL, ec1);
                bar(ex1, 0+es, ex1+71, -100+es);

                if(fc == 0)
                    es += x+1;
                else if(fc == 1)
                    es += x+6;

                if(es >= gH+100)
                {
                    et = 0;
                    et1 = 0;
                    es = 1;
                }
            //CAR 1-->

            //My Car---->
                setfillstyle(SOLID_FILL, LIGHTRED);
                bar(cmx, cmy, cmx+60, cmy+80);

                if(GetAsyncKeyState(VK_LEFT) && cmx >= gW/3+10)
                {
                    cmx -= x;
                }
                else if(GetAsyncKeyState(VK_RIGHT) && cmx+60 <= gW*2/3-10)
                {
                    cmx += x;
                }
                else if(GetAsyncKeyState(VK_UP) && cmy >= 0)
                {
                    cmy -= x;
                }
                else if(GetAsyncKeyState(VK_DOWN) && cmy+80 <= gH)
                {
                    cmy += x;
                }
            //My Car----<

            //Crash logic
            if(
               (((cmx >= ex && cmx <= ex+71) || (cmx+60 >= ex && cmx+60 <= ex+71)) && (cmy <= es && (cmy >= es-100 || cmy+80 >= es-100))) ||
               (((cmx >= ex1 && cmx <= ex1+71) || (cmx+60 >= ex1 && cmx+60 <= ex1+71)) && (cmy <= es && (cmy >= es-100 || cmy+80 >= es-100)))
              )
            {
                Beep(1000,10);
                page1 = 0;
                goto GAME_OVER;
            }

        page = 1 - page;
        delay(20);

        //buttons
        // exit Button
        tW = textwidth(exitText);
        tH = textheight(exitText);
        if((mousex() >= ( gW/6-tW/2 - 4 )) && (mousex() <= ( gW/6-tW/2 + 84 )) && (mousey() >= ( ((gH/2-tH/2)+tH/2) +2 )) && (mousey() <= ( ((gH/2-tH/2)+tH/2) + 40 )))
        {
            setfillstyle(SOLID_FILL, LIGHTBLUE);
            bar(gW/6-tW/2 - 4, ((gH/2-tH/2)+tH/2) +2, gW/6-tW/2 + 84, ((gH/2-tH/2)+tH/2) + 40);
            setcolor(LIGHTBLUE);
            outtextxy(gW/6-tW/2, (gH/2-tH/2)+tH/2+5, exitText);
        }
        if((mousex() >= ( gW/6-tW/2 - 4 )) && (mousex() <= ( gW/6-tW/2 + 84 )) && (mousey() >= ( ((gH/2-tH/2)+tH/2) +2 )) && (mousey() <= ( ((gH/2-tH/2)+tH/2) + 40 )) && GetAsyncKeyState(VK_LBUTTON))
        {
            Beep(4000,100);
            delay(bd);
            goto END;
        }
        // exit Button

        // End Button
        tW = textwidth(endText);
        tH = textheight(endText);
        if((mousex() >= ( gW/6-tW/2 - 4 )) && (mousex() <= ( gW/6-tW/2 + 64 )) && (mousey() >= ( (gH/2-tH/2)-tH/2 - 8 )) && (mousey() <= ( (gH/2-tH/2)-tH/2 + 30 )))
        {
            setfillstyle(SOLID_FILL, LIGHTBLUE);
            bar(gW/6-tW/2 - 4, (gH/2-tH/2)-tH/2 - 8, gW/6-tW/2 + 64, (gH/2-tH/2)-tH/2 + 30);
            setcolor(LIGHTBLUE);
            outtextxy(gW/6-tW/2, (gH/2-tH/2)-tH/2-5, endText);
        }
        if((mousex() >= ( gW/6-tW/2 - 4 )) && (mousex() <= ( gW/6-tW/2 + 64 )) && (mousey() >= ( (gH/2-tH/2)-tH/2 - 8 )) && (mousey() <= ( (gH/2-tH/2)-tH/2 + 30 )) && GetAsyncKeyState(VK_LBUTTON))
        {
            Beep(4000,100);
            delay(bd);
            goto FIRST_SCREEN;
        }
        // End Button
    }

    GAME_OVER:
        while(1)
        {
            setactivepage(page1);
            setvisualpage(1-page1);
            cleardevice();

            setfillstyle(SOLID_FILL, LIGHTGREEN);
            bar(0, 0, gW, gH);

            setfillstyle(SOLID_FILL, DARKGRAY); //8
            bar(gW/3, 0, gW*2/3, gH);

            //Text--->
            settextstyle(8, HORIZ_DIR, 15);
            setcolor(WHITE);

            //Retry text
            char retryText[6] = "Retry";
            tW = textwidth(retryText);
            tH = textheight(retryText);
            setfillstyle(SOLID_FILL, WHITE);
            bar(gW/6-tW/2 - 4, (gH/2-tH/2)-tH/2 - 8, gW/6-tW/2 + 104, (gH/2-tH/2)-tH/2 + 30);
            outtextxy(gW/6-tW/2, (gH/2-tH/2)-tH/2-5, retryText);

            //Exit text
            char exitText[5] = "Exit";
            tW = textwidth(exitText);
            tH = textheight(exitText);
            setfillstyle(SOLID_FILL, WHITE);
            bar(gW/6-tW/2 - 4, ((gH/2-tH/2)+tH/2) +2, gW/6-tW/2 + 84, ((gH/2-tH/2)+tH/2) + 40);
            outtextxy(gW/6-tW/2, (gH/2-tH/2)+tH/2+5, exitText);

            //High Score text
            char highscoreText[20];
            sprintf(highscoreText, "Best Score:%d", highscore);
            tW = textwidth(highscoreText);
            tH = textheight(highscoreText);
            outtextxy((gW+(gW*2)/3)/2 - tW/2, (gH/2-tH/2)-tH/2-5, highscoreText);

            //Score text
            char scoreText[20];
            sprintf(scoreText, "Score:%d", score);
            tW = textwidth(scoreText);
            tH = textheight(scoreText);
            outtextxy((gW+(gW*2)/3)/2 - tW/2, (gH/2-tH/2)+tH/2+5, scoreText);


            //Text---<

            //Road--->
            //Side_line
            setfillstyle(SOLID_FILL, WHITE);
            bar((gW/3)-5, 0, (gW/3)+5, gH);
            bar((gW*2/3)-5, 0, (gW*2/3)+5, gH);

            ///middle lines
            for(i = 0; i <= gH; i += 40)
            {
                //Middle Border
                setfillstyle(SOLID_FILL, WHITE);
                bar((gW/2)-5, i+j, (gW/2)+5, i+25+j);
            }
            //Road---<

            // Enemy car
            setfillstyle(SOLID_FILL, ec);
            bar(ex, 0+es, ex+71, -100+es);

            setfillstyle(SOLID_FILL, ec1);
            bar(ex1, 0+es, ex1+71, -100+es);

            //My car
            setfillstyle(SOLID_FILL, LIGHTRED);
            bar(cmx, cmy, cmx+60, cmy+80);


            if(color > 16)
                color = 1;

            setcolor(color);

            //GameOver text
            settextstyle(8, 0, 18);
            char gameoverText[20] = "GAMEOVER";
            tW = textwidth(gameoverText);
            tH = textheight(gameoverText);
            outtextxy((gW-tW)/2, (gH-tH)/2-145, gameoverText);
            settextstyle(8, HORIZ_DIR, 15);

            //for writing in file
            if(score > highscore)
            {
                HS = fopen("score.txt", "w");
                fprintf(HS, "%d", score);
                fclose(HS);
            }

            if(score > highscore || check == 1)
            {
                check = 1;
                highscore = score;

                //HighScore text
                settextstyle(8, 0, 14);
                char highscoreText1[20] = "Congratulations!!";
                tW = textwidth(highscoreText1);
                tH = textheight(highscoreText1);
                outtextxy((gW-tW)/2, (gH-tH)/2-97, highscoreText1);

                char highscoreText2[25];
                sprintf(highscoreText2, "New Best Score:%d", highscore);
                tW = textwidth(highscoreText2);
                tH = textheight(highscoreText2);
                outtextxy((gW-tW)/2, (gH-tH)/2-70, highscoreText2);
                settextstyle(8, HORIZ_DIR, 15);
            }

            delay(20);
            color++;

            if(co <= 3)
            {
                //Starting text
                setcolor(LIGHTRED);
                char StartingText[20];
                sprintf(StartingText, "Starting In %d", co);
                tW = textwidth(StartingText);
                tH = textheight(StartingText);
                outtextxy((gW-tW)/2, (gH-tH)/2, StartingText);
                delay(500);
                if(co == 0)
                    goto START;
                co--;
            }

            page1 = 1-page1;
            delay(20);

            // exit Button
            tW = textwidth(exitText);
            tH = textheight(exitText);
            if((mousex() >= ( gW/6-tW/2 - 4 )) && (mousex() <= ( gW/6-tW/2 + 84 )) && (mousey() >= ( ((gH/2-tH/2)+tH/2) +2 )) && (mousey() <= ( ((gH/2-tH/2)+tH/2) + 40 )))
            {
                setfillstyle(SOLID_FILL, LIGHTBLUE);
                bar(gW/6-tW/2 - 4, ((gH/2-tH/2)+tH/2) +2, gW/6-tW/2 + 84, ((gH/2-tH/2)+tH/2) + 40);
                setcolor(LIGHTBLUE);
                outtextxy(gW/6-tW/2, (gH/2-tH/2)+tH/2+5, exitText);
            }
            if((mousex() >= ( gW/6-tW/2 - 4 )) && (mousex() <= ( gW/6-tW/2 + 84 )) && (mousey() >= ( ((gH/2-tH/2)+tH/2) +2 )) && (mousey() <= ( ((gH/2-tH/2)+tH/2) + 40 )) && GetAsyncKeyState(VK_LBUTTON))
            {
                Beep(4000,100);
                delay(bd);
                goto END;
            }
            // exit Button

            // Retry Button
            tW = textwidth(retryText);
            tH = textheight(retryText);
            if((mousex() >= ( gW/6-tW/2 - 4 )) && (mousex() <= ( gW/6-tW/2 + 104 )) && (mousey() >= ( (gH/2-tH/2)-tH/2 - 8 )) && (mousey() <= ( (gH/2-tH/2)-tH/2 + 30 )))
            {
                setfillstyle(SOLID_FILL, LIGHTBLUE);
                bar(gW/6-tW/2 - 4, (gH/2-tH/2)-tH/2 - 8, gW/6-tW/2 + 104, (gH/2-tH/2)-tH/2 + 30);
                setcolor(LIGHTBLUE);
                outtextxy(gW/6-tW/2, (gH/2-tH/2)-tH/2-5, retryText);
            }
            if((mousex() >= ( gW/6-tW/2 - 4 )) && (mousex() <= ( gW/6-tW/2 + 104 )) && (mousey() >= ( (gH/2-tH/2)-tH/2 - 8 )) && (mousey() <= ( (gH/2-tH/2)-tH/2 + 30 )) && GetAsyncKeyState(VK_LBUTTON))
            {
                cc = 0;
                Beep(4000,100);
                co = 3;
            }
            // Retry Button

            //Full Screen Box Buttorn
            //Big box
            setfillstyle(SOLID_FILL, WHITE);
            bar(gW-49, gH-49, gW-11, gH-9);
            //small box
            setfillstyle(SOLID_FILL, LIGHTBLUE);
            if(fc == 0)
                bar(gW-30, gH-30, gW-15, gH-13);
            if(fc == 1)
                bar(gW-45, gH-45, gW-30, gH-28);

            //Exit screen button on
            if((mousex() >= ( gW-49 )) && (mousex() <= ( gW-11 )) && (mousey() >= ( gH-49 )) && (mousey() <= ( gH-9 )) && fc == 0)
            {
                //big box
                setfillstyle(SOLID_FILL, LIGHTBLUE);
                bar(gW-49, gH-49, gW-11, gH-9);
                //Middel box
                setfillstyle(SOLID_FILL, WHITE);
                bar(gW-45, gH-45, gW-15, gH-13);
            }
            //Full Screen Button off
            if((mousex() >= ( gW-49 )) && (mousex() <= ( gW-11 )) && (mousey() >= ( gH-49 )) && (mousey() <= ( gH-9 )) && fc == 1)
            {
                //big box
                setfillstyle(SOLID_FILL, LIGHTBLUE);
                bar(gW-49, gH-49, gW-11, gH-9);
                //Middel box
                setfillstyle(SOLID_FILL, WHITE);
                bar(gW-45, gH-45, gW-15, gH-13);
                //Small box
                setfillstyle(SOLID_FILL, LIGHTBLUE);
                bar(gW-30, gH-30, gW-15, gH-13);
            }
            //Full Screen Exit Logic
            //Full Screen Box Button Logic
            if((mousex() >= ( gW-49 )) && (mousex() <= ( gW-11 )) && (mousey() >= ( gH-49 )) && (mousey() <= ( gH-9 )) && GetAsyncKeyState(VK_LBUTTON) && fc == 0)
            {
                fc = 1;
                Beep(4000, 100);
                gW = sW;
                gH = sH;
                cmx = cmx + 171;
                cmy = cmy + 190;
                ex = ex + 171;
                ex1 = ex1 + 171;
                es = es + 190;
                window2 = initwindow(gW, gH, "", -3, -3);
                closegraph(window1);
                delay(100);
                setcurrentwindow(window2);
            }
            //Full Screen Box Button Logic
            //Full Screen Exit Logic
            if((mousex() >= ( gW-49 )) && (mousex() <= ( gW-11 )) && (mousey() >= ( gH-49 )) && (mousey() <= ( gH-9 )) && GetAsyncKeyState(VK_LBUTTON) && fc == 1)
            {
                fc = 0;
                Beep(4000, 100);
                gW = 1024;
                gH = 576;
                cmx = cmx - 171;
                cmy = cmy - 190;
                ex = ex - 171;
                ex1 = ex1 - 171;
                es = es - 190;
                window1 = initwindow(gW, gH, "Box Mover GAME", (sW-gW)/2, (sH-gH)/2);
                closegraph(window2);
                delay(100);
                setcurrentwindow(window1);
            }
            //Full Screen Exit Logic

            //Start Credit Button
            //Credit--->
            char creditText[7] = "Credit";
            tW = textwidth(creditText);
            tH = textheight(creditText);
            setfillstyle(SOLID_FILL, WHITE);
            setcolor(WHITE);
            if(cc == 1)
            {
                setfillstyle(SOLID_FILL, LIGHTBLUE);
                setcolor(LIGHTBLUE);
            }
            bar(gW-tW-60-5, gH-45-4, gW-55, gH-9);
            outtextxy(gW-tW-60, gH-45, creditText);

            //Credit Text
            if(cc == 1)
            {
                setcolor(LIGHTBLUE);
                char nameText[20] = "Md Noor E Musa";
                tW = textwidth(nameText);
                tH = textheight(nameText);
                outtextxy((gW-tW)/2, (gH-tH)/2, nameText);
                char idText[15] = "ID:18CSE033";
                tW = textwidth(idText);
                tH = textheight(idText);
                outtextxy((gW-tW)/2, (gH-tH)/2+35, idText);
            }

            //Credit Button
            tW = textwidth(creditText);
            tH = textheight(creditText);
            if((mousex() >= ( gW-tW-60-5 )) && (mousex() <= ( gW-55 )) && (mousey() >= ( gH-45-4 )) && (mousey() <= ( gH-9 )) && cc==0)
            {
                setfillstyle(SOLID_FILL, LIGHTBLUE);
                bar(gW-tW-60-5, gH-45-4, gW-55, gH-9);
                setcolor(LIGHTBLUE);
                outtextxy(gW-tW-60, gH-45, creditText);
            }
            //Credit on
            if((mousex() >= ( gW-tW-60-5 )) && (mousex() <= ( gW-55 )) && (mousey() >= ( gH-45-4 )) && (mousey() <= ( gH-9 )) && GetAsyncKeyState(VK_LBUTTON) && cc == 0)
            {
                Beep(4000, 100);
                delay(bd);
                cc = 1;
            }
            //Credit off
            if((mousex() >= ( gW-tW-60-5 )) && (mousex() <= ( gW-55 )) && (mousey() >= ( gH-45-4 )) && (mousey() <= ( gH-9 )) && cc == 1)
            {
                setfillstyle(SOLID_FILL, WHITE);
                bar(gW-tW-60-5, gH-45-4, gW-55, gH-9);
                setcolor(WHITE);
                outtextxy(gW-tW-60, gH-45, creditText);
            }
            //Credit on
            if((mousex() >= ( gW-tW-60-5 )) && (mousex() <= ( gW-55 )) && (mousey() >= ( gH-45-4 )) && (mousey() <= ( gH-9 )) && GetAsyncKeyState(VK_LBUTTON) && cc == 1)
            {
                Beep(4000, 100);
                delay(bd);
                cc = 0;
            }
            //End of Credit Button
        }

    END:
        closegraph();

//Code---<
}
