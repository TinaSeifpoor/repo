function [transEst, emitEst, initProbEst ,logProb] = HMMtrain(seq, transInitial, emitInitial, initProbInitial,maxIters)
%%
T = size(seq,2);
[N,M] = size(emitInitial);
nSamples = size(seq,1);
%%
liTrain = zeros(maxIters,nSamples);
for idxIt=1:maxIters
    if (idxIt>1)
        transInitial = mean(AList,3);
        emitInitial = mean(BList,3);
        initProbInitial = mean(PiList,3);
    end
    AList = zeros(N,N,nSamples);
    BList = zeros(N,M,nSamples);
    PiList = zeros(1,N,nSamples);
    for idxInst=1:nSamples
        O=seq(idxInst,:);
        [logProbSeq,trNew,emitNew,PiNew] = HMMCalcSeq(transInitial,emitInitial,initProbInitial,T,M,N,O);
        AList(:,:,idxInst) = trNew;
        BList(:,:,idxInst) = emitNew;
        PiList(:,:,idxInst) = PiNew;
        % Log likelihood
        liTrain(idxIt, idxInst) = logProbSeq;
    end
end
transEst = mean(AList,3);
emitEst = mean(BList,3);
initProbEst = mean(PiList,3);
logProb = liTrain(end,:);
end

function [logProb,A,B,Pi] = HMMCalcSeq(A,B,Pi,T,M,N,O)
%% Forward->
% Compute alpha t=0
c(1) = 0;
for i=1:N
    a(1,i) = Pi(i)*B(i,O(1));
    c(1) = c(1) + a(1,i);
end

c(1) = 1/c(1);
for i=1:N
    a(1,i) = c(1)*a(1,i);
end

for t = 2:T
    c(t) = 0;
    for i=1:N
        a(t,i) = 0;
        for j=1:N
            a(t,i) = a(t,i) + a(t-1,j)*A(j,i);
        end
        a(t,i) = a(t,i)*B(i,O(t));
        c(t) = c(t) + a(t,i);
    end
    c(t) = 1/c(t);
    for i=1:N
        a(t,i) = c(t)*a(t,i);
    end
end

%% Backward<-
% Compute beta t=0
for i = 1:N
    b(T,i) = c(T);
end
% Compute beta t
for t = T-1:-1:1
    for i=1:N
        b(t,i) = 0;
        for j = 1:N
            b(t,i) = b(t,i)+A(i,j)*B(j,O(t+1))*b(t+1,j);
        end
        b(t,i) = c(t)*b(t,i);
    end
end


%% Compute gamma
seqProb = sum(a(T,:));
for t=1:T-1
    denom = 0;
    for i=1:N
        for j=1:N
            denom = denom+a(t,i)*A(i,j)*B(j,O(t+1))*b(t+1,j);
        end
    end
    for i=1:N
        gs(t,i) = 0;
        for j=1:N
            g(t,i,j) = (a(t,i)*A(i,j)*B(j,O(t+1))*b(t+1,j))/denom;
            gs(t,i) = gs(t,i) + g(t,i,j);
        end
    end
end

%% Re-estimate A,B & Pi
% Pi
for i=1:N
    Pi(i) = gs(1,i);
end
% A
for i=1:N
    for j=1:N
        numer=0;
        denom=0;
        for t=1:T-1
            numer = numer + g(t,i,j);
            denom = denom + gs(t,i);
        end
        A(i,j) = numer/denom;
    end
end
% B
for i=1:N
    for j=1:M
        numer=0; denom=0;
        for t=1:T-1
            if (O(t) == j)
                numer = numer+gs(t,i);
            end
            denom = denom+gs(t,i);
        end
        B(i,j) = numer/denom;
    end
end

logProb = 0;
for i=1:T
    logProb = logProb + log(c(i));
end
logProb = -logProb;

end

