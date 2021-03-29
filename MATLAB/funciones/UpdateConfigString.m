function UpdateConfigString(caller, hObj)
% caller:   indica desde qué callback se llamó a la función.
%       1 => pushbutton para configurar EA
%       2 => pushbutton para configurar Fs 

    hs = guidata(hObj);
    info = getappdata(hs.Figure,'info');
    modeADC = getappdata(hs.Figure,'modeADC');
    
    % Obtengo información de la plataforma seleccionada actualmente
    plataforma = get(hs.ButGroup_Plataforma,'selectedobject');

    %% Según el callback que llamó a esta función:
    
    if(caller==1)
        
        % Obtengo el dato del popup EA

        if( plataforma == hs.RadioBut_LPC1769 )
            aux_EA = get(hs.Popup_EA,'string');
            val_EA = get(hs.Popup_EA,'value');
            aux_EA = aux_EA{val_EA};
            aux_EA = aux_EA(end);
            aux_Fs = modeADC.LPC1769.Fs;
        end
        
        if( plataforma == hs.RadioBut_LPC845 )
            aux_EA = get(hs.Popup_EA_LPC845,'string');
            val_EA = get(hs.Popup_EA_LPC845,'value');
            aux_EA = aux_EA{val_EA};
            aux_Fs = modeADC.LPC845.Fs;
        end
        
    end
        
    if(caller==2)
        % Obtengo el dato del popup Fs
        aux_Fs = get(hs.Popup_Fs,'string');
        val_Fs = get(hs.Popup_Fs,'value');
        aux_Fs = aux_Fs{val_Fs};
        
        if(plataforma == hs.RadioBut_LPC1769)
            aux_EA = modeADC.LPC1769.EA_infotronic;
            aux_EA = aux_EA(end);
        end
        
        if( plataforma == hs.RadioBut_LPC845 )
            aux_EA = modeADC.LPC845.channel;
        end

    end
        
    %% Actualizo la string con la configuración actual, según la plataforma
    
    % infotronic v1
    if(plataforma == hs.RadioBut_LPC1769)
        aux_string = 'EA';
        aux_string = strcat(aux_string, aux_EA);
        aux_string = strcat(aux_string, ', ');
        aux_string = strcat(aux_string, aux_Fs);
        aux_string = strcat(aux_string, ' Hz.');
        
        set(hs.strDisplayConfig, 'string', aux_string);
    end
    
    % arduino
    if(plataforma == hs.RadioBut_Arduino)
        aux_string = 'Pin A0';
        aux_string = strcat(aux_string, ', ');
        aux_string = strcat(aux_string, aux_Fs);
        aux_string = strcat(aux_string, ' Hz.');
        
        set(hs.strDisplayConfig_ARDUINO, 'string', aux_string);
    end
    
    % LPC845
    if(plataforma == hs.RadioBut_LPC845)
        aux_string = strcat(aux_EA, ', ');
        aux_string = strcat(aux_string, aux_Fs);
        aux_string = strcat(aux_string, ' Hz.');
        
        set(hs.strDisplayConfig_LPC845, 'string', aux_string);
    end
    
    setappdata(hs.Figure,'info',info);    
    setappdata(hs.Figure,'modeADC', modeADC);
    guidata(hObj, hs);
end

% Este callback actualiza la string que muestra la configuración actual.