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
a = zeros(T,N);
a(1,:) = Pi.*B(:,O(1))';
% Compute alpha t
for t = 2:T
    a(t,:)=sum(bsxfun(@times,A',a(t-1,:)),2).*B(:,O(t));
end
%% Backward<-
% Compute beta t=0
b = ones(T,N);
% Compute beta t
for t = T-1:-1:1
    b(t,:) = sum(bsxfun(@times, A,B(:,O(t+1))'.*b(t+1,:)),2);
end

%% Compute gamma
seqProb = sum(a(T,:));
for t = 1:T-1
    g(t,:,:) = bsxfun(@times,bsxfun(@times, A, a(t,:)'),B(:,O(t+1))'.*b(t+1,:))./seqProb;
end
% Log likelihood
logProb=log(sum(a(T,:)));

%% Re-estimate A,B & Pi
% Pi
Pi = reshape(sum(sum(g(1,:,:),3),3),1,N);
% A
A(:,:) = bsxfun(@rdivide,sum(g(1:T-1,:,:)),sum(sum(g(1:T-1,:,:),3)));
% B
for i=1:N
    for j=1:M
        numer=0; seqProb=0;
        for t=1:T-1
            if (O(t) == j)
                numer = numer+sum(g(t,i,:));
            end
            seqProb = seqProb+sum(g(t,i,:));
        end
        B(i,j) = numer/seqProb;
    end
end

end

