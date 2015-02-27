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
## @deftypefn {Function File} {@var{retval} =} genProb (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: csari <csari@ISRA-CSARI>
## Created: 2015-02-26

function [prob, letters] = genProb (names)
letters = 0:max(max(names));
%% initialProbabilities;
initProb = calculatePDF(names(:,1),letters);
%% transitionProbabilities;
transProb = zeros(length(letters));
transProb2 = zeros(length(letters),length(letters),length(letters));
for idxCol=1:size(names,2)-1
  curCol = names(:,idxCol);
  nexCol = names(:,idxCol+1);
  for idxLet=1:length(letters)
    curLetter = letters(idxLet);
    curColSampleIdx = curCol==curLetter;
    nexColLetters = nexCol(curColSampleIdx);
    transProb(idxLet,:) = transProb(idxLet,:)+calculatePDF(nexColLetters,letters,false);    
    if (idxCol<size(names,2)-2)
      for idxLet2=1:length(letters)
        nexLetter = letters(idxLet2);
        nexColSampleIdx = nexColLetters==nexLetter;
        nnexCol = names(:,idxCol+2);
        nnexCol = nnexCol(curColSampleIdx);
        nnexColLetters = nnexCol(nexColSampleIdx);
        oldProb = transProb2(idxLet, idxLet2,:);
        curProb = calculatePDF(nnexColLetters,letters,false)';
        newProb = squeeze(oldProb) + squeeze(curProb);
        transProb2(idxLet, idxLet2,:) = newProb;
      end
    end
  end
end
prob{1} = initProb;
prob{2} = transProb;
prob{3} = transProb2;
endfunction
