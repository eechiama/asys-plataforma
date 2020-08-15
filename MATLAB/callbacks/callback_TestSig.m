function callback_TestSig(hObj, event)

hs = guidata(hObj.Parent);
info = getappdata(hs.Figure,'info');

% si no hay serial port abierto
if info.SerialOpened==0
    errordlg('No hay ningún puerto abierto.');
    return;
end

% si se está muestreando
if info.Sampling == 1
    errordlg('No se puede recibir una señal de prueba durante el muestreo.')
    return;
end

% Si el puerto serie está abierto e inactivo
if info.Sampling == 0
    
    % Vacío el input buffer del serial
    flushinput(hs.Serial);
    
    % preparo el comando para enviar
    string_command = '$T1#';
    
    % envío el comando
    fprintf(hs.Serial, string_command);
    
    % actualizo el flag
    info.TestSignal = 1;
    
end

setappdata(hs.Figure,'info',info);
guidata(hObj.Parent,hs);

end