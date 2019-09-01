function UpdateConfigString(caller, hObj)

    hs = guidata(hObj);
    info = getappdata(hs.Figure,'info');
    modeADC = getappdata(hs.Figure,'modeADC');
    
    % Obtengo información de la plataforma seleccionada actualmente
    plataforma = get(hs.ButGroup_Plataforma,'selectedobject');

    if(caller==1)   % Solo sucede en caso de plataforma = infotronic
        % Obtengo el dato del popup EA
        aux_EA = get(hs.Popup_EA,'string');
        val_EA = get(hs.Popup_EA,'value');
        aux_EA = aux_EA{val_EA};
        aux_EA = aux_EA(end);
        
        aux_Fs = modeADC.FsActual;
    end
        
    if(caller==2)
        
        % Obtengo el dato del popup Fs
        aux_Fs = get(hs.Popup_Fs,'string');
        val_Fs = get(hs.Popup_Fs,'value');
        aux_Fs = aux_Fs{val_Fs};
        
        if(plataforma == hs.RadioBut_Infotronic)
            aux_EA = modeADC.EAActual;
            aux_EA = aux_EA(end);
        end

    end
        
    % Actualizo la string con la configuración actual
    if(plataforma == hs.RadioBut_Infotronic)
        aux_string = 'EA';
        aux_string = strcat(aux_string, aux_EA);
        aux_string = strcat(aux_string, ', ');
        aux_string = strcat(aux_string, aux_Fs);
        aux_string = strcat(aux_string, ' Hz.');
        
        set(hs.Text_DisplayConfig, 'string', aux_string);
    end
    
    % Actualizo la string con la configuración actual
    if(plataforma == hs.RadioBut_Arduino)
        aux_string = 'Pin A0';
        aux_string = strcat(aux_string, ', ');
        aux_string = strcat(aux_string, aux_Fs);
        aux_string = strcat(aux_string, ' Hz.');
        
        set(hs.Text_DisplayConfig_ARDUINO, 'string', aux_string);
    end
    
    setappdata(hs.Figure,'info',info);    
    setappdata(hs.Figure,'modeADC', modeADC);
    guidata(hObj, hs);
end

% Este callback actualiza la string que muestra la configuración actual.