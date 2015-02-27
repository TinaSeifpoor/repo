## Copyright (C) 2015 csari
## 
## This program is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 3 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.

## -*- texinfo -*- 
## @deftypefn {Function File} {@var{retval} =} readText (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: csari <csari@ISRA-CSARI>
## Created: 2015-02-26

function names = readText (filename)
fid = fopen(filename);
word = fgetl(fid);
names = int16([]);
while ischar(word)
  if (length(word)>20)
    continue
  end
  integerWord = int16(word);
  integerWord(1) = integerWord(1)+32;
  integerWord = integerWord-95;
  names(size(names,1)+1,:) = [integerWord,1,zeros(1,25-length(integerWord))];
  word = fgetl(fid);
end
endfunction
