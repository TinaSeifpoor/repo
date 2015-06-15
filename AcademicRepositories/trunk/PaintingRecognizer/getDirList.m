function fileList = getDirList(path)
entryList=dir(path);
isubfile = cell2mat({entryList(:).isdir});
fileList = {entryList(isubfile).name};
fileList = fileList(3:end);
end
