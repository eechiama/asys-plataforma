function callback_check_bytes(hObj, event)

hs = guidata(hObj.Parent);
info = getappdata(hs.Figure,'info');

% si no hay serial port abierto
if info.SerialOpened==0
    errordlg('No hay ningún puerto abierto.');
    return;
end

remaining = get(hs.Serial,'bytesavailable');
set(hs.Text_Remaining, 'string', remaining);

guidata(hObj.Parent,hs);

end