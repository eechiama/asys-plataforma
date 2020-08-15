function callback_Configurar_Fs(hObj, event)

hs = guidata(hObj.Parent);
info = getappdata(hs.Figure,'info');
modeADC = getappdata(hs.Figure,'modeADC');

%% si no hay serial port abierto
if info.SerialOpened==0
    errordlg('No se puede configurar FS sin ningún puerto serie abierto.');
    return;
end

%% serial port abierto e inactivo
if info.Sampling == 0
    
    % preparo el comando
    string_command = '$C,';
    string_command = strcat(string_command, modeADC.FsToSet);
    string_command = strcat(string_command,'.#');
    
    % envío el comando
    fprintf(hs.Serial, string_command);
    
    % Obtengo información de la plataforma seleccionada actualmente
    plataforma = get(hs.ButGroup_Plataforma,'selectedobject');

    %% Actualizo según la plataforma seleccionada
    if( plataforma == hs.RadioBut_Infotronic )
        % la Fs
        modeADC.LPC1769.Fs = modeADC.FsToSet;
        
        % La cantidad de samples a leer del puerto serie de a una vez
        info.SamplesToRead_LPC1769 = ( str2double(modeADC.LPC1769.Fs) / info.MedianaSize ) / 5;
        info.SamplesToRead = info.SamplesToRead_LPC1769;
    end
    
    if( plataforma == hs.RadioBut_LPC845 )
        % la Fs
        modeADC.LPC845.Fs = modeADC.FsToSet;
        
        % La cantidad de samples a leer del puerto serie de a una vez
        info.SamplesToRead_LPC845 = ( str2double(modeADC.LPC845.Fs) / info.MedianaSize ) / 5;
        info.SamplesToRead = info.SamplesToRead_LPC845;
    end

    if(plataforma == hs.RadioBut_Arduino)
        % la Fs
        modeADC.Arduino.Fs = modeADC.FsToSet;
        
        % La cantidad de samples a leer del puerto serie de a una vez
        info.SamplesToRead_ARDUINO = ( str2double(modeADC.Arduino.Fs) / info.MedianaSize ) / 5;
        info.SamplesToRead = info.SamplesToRead_ARDUINO;
    end
    
    % Actualizar datos
    setappdata(hs.Figure,'info',info);
    setappdata(hs.Figure,'modeADC',modeADC);
    guidata(hObj.Parent,hs);
    
    % Actualizo el DisplayConfig string
    UpdateConfigString(2,hObj);
    
    msgbox('Configuración realizada.');
end

end