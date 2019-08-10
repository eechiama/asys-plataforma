function callback_PlataformaChanged(hObj, event)

hs = guidata(hObj.Parent);
info = getappdata(hs.Figure,'info');

% Obtengo información de la selección de plataforma
new_select = get(hs.ButGroup_Plataforma,'selectedobject');

if(new_select == hs.RadioBut_Infotronic)
    old_select = hs.RadioBut_Arduino;
end

if(new_select == hs.RadioBut_Arduino)
    old_select = hs.RadioBut_Infotronic;
end

% si se está en medio del muestreo
if info.Sampling==1
    errordlg('No se puede cambiar la plataforma en medio del muestreo.');
    set(hs.ButGroup_Plataforma,'selectedobject',old_select);
    % update fig data
    setappdata(hs.Figure,'info',info);
    guidata(hObj.Parent,hs);
    return;
end

% Si la plataforma es Arduino, oculto lo no implementado
if new_select == hs.RadioBut_Arduino
    
    % Display Config
     set(hs.Text_DisplayConfig,'visible','off');
     set(hs.Text_DisplayConfig_ARDUINO,'visible','on');
    
    % Config de Entrada Analógica
    set(hs.Text_Entrada,'visible','off');
    set(hs.Popup_EA,'visible','off');
    set(hs.Push_Config_EA,'visible','off');
    
    % Arduino input pin
    set(hs.Text_NoArduinoConfig2,'visible','on');
    
    % Test Signal 3
    set(hs.Push_Test3,'visible','on');
    
    % ylim adecuado al adc de 10bits
    set(hs.Edit_Ylim2,'string','1024','fontsize',15);
    
    reset_plot(hs);
    
    info.SamplesToRead = info.SamplesToRead_ARDUINO;
    
end


% Si la plataforma es el kit de Info, muestro la configuración
if new_select == hs.RadioBut_Infotronic
    
    % Display Config
     set(hs.Text_DisplayConfig,'visible','on');
     set(hs.Text_DisplayConfig_ARDUINO,'visible','off');
    
    % Config de Entrada Analógica
    set(hs.Text_Entrada,'visible','on');
    set(hs.Popup_EA,'visible','on');
    set(hs.Push_Config_EA,'visible','on');
    
    % Arduino input pin
    set(hs.Text_NoArduinoConfig2,'visible','off');
    
    % Test Signal 3
    set(hs.Push_Test3,'visible','off');
    
    % ylim adecuado al adc de 12bits
    set(hs.Edit_Ylim2,'string','4096','fontsize',15);
    
    reset_plot(hs);
    
    info.SamplesToRead = info.SamplesToRead_M3;
    
end


% update fig data
setappdata(hs.Figure,'info',info);
guidata(hObj.Parent,hs);

end

