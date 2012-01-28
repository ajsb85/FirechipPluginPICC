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

long report_line_number;


void report_data_line(int16 data){

   fprintf( PC, "%4lu  Data: %5lu\r\n", report_line_number++, data);

}

void report_error(errors error){

   switch( error ) {
     case err_range    :  fprintf( PC, "%4lu  DATA POINT OUT OF RANGE\r\n", report_line_number++);
     case err_too_far  :  fprintf( PC, "%4lu  DATA POINT TOO FAR FROM PREVIOUS POINT\r\n", report_line_number++);
     case err_too_many :  fprintf( PC, "%4lu  TOO MANY DATA POINTS\r\n", report_line_number++);
   }
}


