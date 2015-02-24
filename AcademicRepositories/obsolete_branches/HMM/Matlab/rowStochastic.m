function matRowStochastic = rowStochastic(mat)
%ROWSTOCHASTIC Makes matrix row-stochastic by dividing it to its sum of
%rows, for each row.
matRowStochastic = bsxfun(@rdivide,mat,sum(mat,2));
end

