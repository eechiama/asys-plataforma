function callback_Configurar_EA(hObj, event)

hs = guidata(hObj.Parent);
info = getappdata(hs.Figure,'info');
modeADC = getappdata(hs.Figure,'modeADC');

% si no hay serial port abierto
if info.SerialOpened==0
    errordlg('No se puede configurar EA sin ningún puerto serie abierto.');
    return;
end

% plataforma actual?
plataforma = get(hs.ButGroup_Plataforma,'selectedobject');

%% Identifico la plataforma y obtengo el código correcto de canal para enviar

if plataforma == hs.RadioBut_LPC1769
    aux = modeADC.LPC1769.EA_to_set(end);
end

if plataforma == hs.RadioBut_LPC845
    aux = modeADC.LPC845.channel_to_set(end);
    if( strcmp(aux, 'Pote') )
       aux = '0'; 
    end
end

%% serial port abierto e inactivo
if info.Sampling == 0
    
    % preparo el comando
    
    string_command = '$I,';
    string_command = strcat(string_command, aux);
    string_command = strcat(string_command,'.#');
    
    % envío el comando
    fprintf(hs.Serial, string_command);
    
    % actualizo la EAActual
    if plataforma == hs.RadioBut_LPC1769
        modeADC.LPC1769.EA_infotronic = modeADC.LPC1769.EA_to_set;
    end
    
    if plataforma == hs.RadioBut_LPC845
        modeADC.LPC845.channel = modeADC.LPC845.channel_to_set;
    end
   
    % Actualizar datos
    setappdata(hs.Figure,'info',info);
    setappdata(hs.Figure,'modeADC',modeADC);
    guidata(hObj.Parent,hs);
    
    % Actualizo el DisplayConfigString
    UpdateConfigString(1,hObj);
    
    msgbox('Configuración realizada.');
end

end