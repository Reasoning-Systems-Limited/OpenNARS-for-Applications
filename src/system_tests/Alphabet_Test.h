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

void NAR_Alphabet_Test()
{
    NAR_INIT();
    puts(">>NAR Alphabet test start");
    NAR_AddInput(Narsese_AtomicTerm("a"), EVENT_TYPE_BELIEF, NAR_DEFAULT_TRUTH, false, false);
    for(int32_t i=0; i<50; i++)
    {
        int32_t k=i%10;
        if(i % 3 == 0)
        {
            char c[2] = {'a'+k,0};
            NAR_AddInput(Narsese_AtomicTerm(c), EVENT_TYPE_BELIEF, NAR_DEFAULT_TRUTH, false, false);
        }
        NAR_Cycles(1);
        puts("TICK");
    }
    puts("<<NAR Alphabet test successful");
}
