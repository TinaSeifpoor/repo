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
## @deftypefn {Function File} {@var{retval} =} calculatePDF (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: csari <csari@ISRA-CSARI>
## Created: 2015-02-26

function densityDistribution = calculatePDF (array, members, isProb)
if (nargin<3)
  isProb=true;
end
densityDistribution = zeros(size(members));
for idxMember = 1:length(members)
  logicalMatches = array==members(idxMember);
  if (isempty(logicalMatches))
    densityDistribution(idxMember) = 0;
  else
    if (isProb)
      densityDistribution(idxMember) = mean(logicalMatches);
    else
      densityDistribution(idxMember) = sum(logicalMatches);
    end
  end
end
endfunction