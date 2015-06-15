function fileList = getFileList(path)
entryList=dir(path);
isubfile = ~cell2mat({entryList(:).isdir});
fileList = {entryList(isubfile).name};
end
