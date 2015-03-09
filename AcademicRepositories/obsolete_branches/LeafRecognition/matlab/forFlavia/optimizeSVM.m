function [perfCV, params]...
    = optimizeSVM(classes, features)
bestcv = 0;
for log2c = 1:.5:5,
    for log2g = -.8,
        cmd = ['-q -v 5 -c ', num2str(2^log2c), ' -g ', num2str(2^log2g)];
        cv = svmtrain(classes, features, cmd);
        if (cv >= bestcv),
            bestcv = cv; bestc = 2^log2c; bestg = 2^log2g;
        end
        fprintf('%g %g %g (best c=%g, g=%g, rate=%g)\n', log2c, log2g, cv, bestc, bestg, bestcv);
    end
end
perfCV = bestcv;
params = [bestc, bestg];