function callback_Configurar_EA(hObj, event)

% esta función sólo se llama con la selección de plataforma LPC1769

hs = guidata(hObj.Parent);
info = getappdata(hs.Figure,'info');
modeADC = getappdata(hs.Figure,'modeADC');

% si no hay serial port abierto
if info.SerialOpened==0
    errordlg('No se puede configurar EA sin ningún puerto serie abierto.');
    return;
end

% serial port abierto e inactivo
if info.Sampling == 0
    
    % preparo el comando
    aux = modeADC.LPC1769.EA_to_set(end);
    string_command = '$I,';
    string_command = strcat(string_command, aux);
    string_command = strcat(string_command,'.#');
    
    % envío el comando
    fprintf(hs.Serial, string_command);
    
    % actualizo la EAActual
    modeADC.LPC1769.EA_infotronic = modeADC.LPC1769.EA_to_set;
    
    % Actualizar datos
    setappdata(hs.Figure,'info',info);
    setappdata(hs.Figure,'modeADC',modeADC);
    guidata(hObj.Parent,hs);
    
    % Actualizo el DisplayConfigString
    UpdateConfigString(1,hObj);
    
    msgbox('Configuración realizada.');
end

end