/* 
<Firechip™ IDE: Is a free (GNU) source code editor for electronics designer.>
 Copyright © 2012 "Alexander Salas" <alexander@firechip.info>

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by 
 the Free Software Foundation, either version 3 of the License, or
 any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.*/
 
#include "project.h"

#include "report.h"

#define WINDOW_SIZE 10

long history[WINDOW_SIZE];
int points, history_ptr;


void filter_clear() {
   points=0;
   history_ptr=0;
}


int32 calculate_average() {
   int i;
   int32 sum;

   for(sum=0,i=0; (i<WINDOW_SIZE) && (i<points); i++)
      sum+=history[i];
   return sum/i;
}


long filter_data(long value) {
   long filtered;
   
   points++;
   history[history_ptr]=value;
   history_ptr=(history_ptr+1) % WINDOW_SIZE;

   filtered = calculate_average();
   if(value > (filtered+100))
     report_error(err_too_far);
   
   return filtered;
}


