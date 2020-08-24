/* 
 * The MIT License
 *
 * Copyright 2020 The OpenNARS authors.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

void NAR_Pong(int32_t iterations)
{
    NAR_INIT();
    puts(">>NAR Pong start");
    NAR_AddOperation(Narsese_AtomicTerm("^left"), NAR_Pong_Left); 
    NAR_AddOperation(Narsese_AtomicTerm("^right"), NAR_Pong_Right); 
    int32_t szX = 50;
    int32_t szY = 20;
    int32_t ballX = szX/2;
    int32_t ballY = szY/5;
    int32_t batX = 20;
    int32_t batVX = 0;
    int32_t batWidth = 4; //"radius", batWidth from middle to the left and right
    int32_t vX = 1;
    int32_t vY = 1;
    int32_t hits = 0;
    int32_t misses = 0;
    int32_t t=0;
    while(1)
    {
        if(iterations != -1 && t++ > iterations)
        {
            break;
        }
        //if(t%10000 == 0)
        //    getchar();
        fputs("\033[1;1H\033[2J", stdout); //POSIX clear screen
        for(int32_t i=0; i<batX-batWidth+1; i++)
        {
            fputs(" ", stdout);
        }
        for(int32_t i=0; i<batWidth*2-1 ;i++)
        {
            fputs("@", stdout);
        }
        puts("");
        for(int32_t i=0; i<ballY; i++)
        {
            for(int32_t k=0; k<szX; k++)
            {
                fputs(" ", stdout);
            }
            puts("|");
        }
        for(int32_t i=0; i<ballX; i++)
        {
            fputs(" ", stdout);
        }
        fputs("#", stdout);
        for(int32_t i=ballX+1; i<szX; i++)
        {
            fputs(" ", stdout);
        }
        puts("|");
        for(int32_t i=ballY+1; i<szY; i++)
        {
            for(int32_t k=0; k<szX; k++)
            {
                fputs(" ", stdout);
            }
            puts("|");
        }
        if(batX < ballX)
        {
            NAR_AddInputBelief(Narsese_AtomicTerm("ball_right"));
        }
        if(ballX < batX)
        {
            NAR_AddInputBelief(Narsese_AtomicTerm("ball_left"));
        }
        NAR_AddInputGoal(Narsese_AtomicTerm("good_nar"));
        if(ballX <= 0)
        {
            vX = 1;
        }
        if(ballX >= szX-1)
        {
            vX = -1;
        }
        if(ballY <= 0)
        {
            vY = 1;
        }
        if(ballY >= szY-1)
        {
            vY = -1;
        }
        ballX += vX;
        ballY += vY;
        if(ballY == 0)
        {
            if(abs(ballX-batX) <= batWidth)
            {
                NAR_AddInputBelief(Narsese_AtomicTerm("good_nar"));
                puts("good");
                hits++;
            }
            else
            {
                puts("bad");
                misses++;
            }
        }
        if(ballY == 0 || ballX == 0 || ballX >= szX-1)
        {
            ballY = szY/2+myrand()%(szY/2);
            ballX = myrand()%szX;
            vX = myrand()%2 == 0 ? 1 : -1;
        }
        if(NAR_Pong_Left_executed)
        {
            NAR_Pong_Left_executed = false;
            puts("Exec: op_left");
            batVX = -2;
        }
        if(NAR_Pong_Right_executed)
        {
            NAR_Pong_Right_executed = false;
            puts("Exec: op_right");
            batVX = 2;
        }
        batX=MAX(0,MIN(szX-1,batX+batVX*batWidth/2));
        printf("Hits=%d misses=%d ratio=%f time=%" PRIu32 "\n", hits, misses, (float) (((float) hits) / ((float) hits + misses)), currentTime);
        if(iterations == -1)
        {
            nanosleep((struct timespec[]){{0, 20000000L}}, NULL); //POSIX sleep
        }
        //NAR_Cycles(10);
    }
}
