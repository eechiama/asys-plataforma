function callback_Configurar_EA(hObj, event)

hs = guidata(hObj.Parent);
info = getappdata(hs.Figure,'info');

% si no hay serial port abierto
if info.SerialOpened==0
    errordlg('No se puede configurar EA sin ningún puerto serie abierto.');
    return;
end

% serial port abierto e inactivo
if info.Sampling == 0
    
    % preparo el comando
    aux = info.EAToSet(end);
    string_command = '$I,';
    string_command = strcat(string_command, aux);
    string_command = strcat(string_command,'.#');
    
    % envío el comando
    fprintf(hs.Serial, string_command);
    
    % actualizo la EAActual
    info.EAActual = info.EAToSet;
    
    % Actualizar datos
    setappdata(hs.Figure,'info',info);
    guidata(hObj.Parent,hs);
    
    % Actualizo el DisplayConfigString
    info = UpdateConfigString(1,hObj);
    
    msgbox('Configuración realizada.');
end

info

end