function outStruct = readRijksXML(xmlFiles)
%READRÝJKSXML Summary of this function goes here
%   Detailed explanation goes here
if (~iscell(xmlFiles))
    xmlFiles = {xmlFiles};
end
for i=1:numel(xmlFiles)
    xmlFile = xmlFiles{i};
    p = xml2struct(xmlFile);
    out = p.record.metadata.oai_dc_colon_dc;
    out2.type  = readEntry(out,'dc_colon_type');
    out2.date  = readEntry(out,'dc_colon_date');
    out2.title = readEntry(out,'dc_colon_title');    
    outStruct(i) = out2;
end

end

function value = readEntry(structName, field)
k = fields(structName);
idx = find(strcmp(k, field));
if (idx)
    evalText = strcat('structName = structName.',field,';');
    eval(evalText);
    if(iscell(structName))
        value='';
        for j=1:numel(structName)
            tCurr = structName{j};
            textCurr = tCurr.Text;
            if (j>1)
                textCurr = strcat(' ', textCurr);
            end
            value = strcat(value,textCurr);
        end
    else
        value = structName.Text;
    end
else
    value = '';
end
end

