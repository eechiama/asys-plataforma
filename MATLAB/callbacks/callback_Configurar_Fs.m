function callback_Configurar_Fs(hObj, event)

hs = guidata(hObj.Parent);
info = getappdata(hs.Figure,'info');

% si no hay serial port abierto
if info.SerialOpened==0
    errordlg('No se puede configurar FS sin ningún puerto serie abierto.');
    return;
end

% serial port abierto e inactivo
if info.Sampling == 0
    
    % preparo el comando
    string_command = '$C,';
    string_command = strcat(string_command, info.FsToSet);
    string_command = strcat(string_command,'.#');
    
    % envío el comando
    fprintf(hs.Serial, string_command);
    
    
    % Obtengo información de la plataforma seleccionada actualmente
    platafoma = get(hs.ButGroup_Plataforma,'selectedobject');

    if(platafoma == hs.RadioBut_Infotronic)
        % actualizo la FsActual
        info.FsActual = info.FsToSet;
        
        % Actualizo la cantidad de samples a leer del puerto serie de a una vez
        info.SamplesToRead_M3 = ( str2double(info.FsActual) / info.MedianaSize ) / 5;
        info.SamplesToRead = info.SamplesToRead_M3;
    end

    if(platafoma == hs.RadioBut_Arduino)
        % actualizo la FsActual_ARDUINO
        info.FsActual_ARDUINO = info.FsToSet;
        
        % Actualizo la cantidad de samples a leer del puerto serie de a una vez
        info.SamplesToRead_ARDUINO = ( str2double(info.FsActual_ARDUINO) / info.MedianaSize ) / 5;
        info.SamplesToRead = info.SamplesToRead_ARDUINO;
    end
    
    % Actualizar datos
    setappdata(hs.Figure,'info',info);
    guidata(hObj.Parent,hs);
    
    % Actualizo el DisplayConfig string
    info = UpdateConfigString(2,hObj);
    
    msgbox('Configuración realizada.');
end

info

end