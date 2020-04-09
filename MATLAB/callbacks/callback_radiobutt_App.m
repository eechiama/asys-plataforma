function callback_radiobutt_App(hObj, event)

hs = guidata(hObj.Parent);
info = getappdata(hs.Figure,'info');

% plataforma actual?
plataforma = get(hs.ButGroup_Plataforma,'selectedobject');

% new selection of app radiobuttons?
new_select = get(hs.ButGroup_App,'selectedobject');

hide_gui_adc(hObj);
hide_gui_generator(hObj);
hide_gui_buttons(hObj);

if new_select == hs.RadioBut_Buttons
    
    % CASE: Plataforma Infotronic
    % show notice that buttons are not implemented on kit infotronic
    if(plataforma == hs.RadioBut_Infotronic)
    set(hs.Text_buttons_NoInfotronic,'visible','on');
    end
    
    % CASE: Plataforma ARDUINO
    % show arduino-specific for buttons app
    if(plataforma == hs.RadioBut_Arduino)
    % arduino
    set(hs.Toggle_Buttons,'visible','on');
    set(hs.Popup_waveform_Buttons,'visible','on');
    % shared objects with generator app for arduino
    set(hs.Text_Signal,'visible','on');
    set(hs.Text_fdiv,'visible','on');
    set(hs.Popup_fdiv,'visible','on');
    end
end


if new_select == hs.RadioBut_Generator
    
    % CASE: Plataforma Infotronic
    % show notice that generator is not implemented on kit infotronic
    if(plataforma == hs.RadioBut_Infotronic)
    set(hs.Text_pwm_NoInfotronic,'visible','on');
    end
    
    % CASE: Plataforma ARDUINO
    % show arduino-specific for generator app
    if(plataforma == hs.RadioBut_Arduino)
    set(hs.Toggle_pwm,'visible','on');
    set(hs.Popup_waveform,'visible','on');
    set(hs.Text_Signal,'visible','on');
    set(hs.Text_fdiv,'visible','on');
    set(hs.Popup_fdiv,'visible','on');
    end
end

%%
if new_select == hs.RadioBut_ADQ    
    % show shared ADQ stuff
    set(hs.Text_Save,'visible','on');
    set(hs.Edit_File,'visible','on');
    
    set(hs.Push_Save,'visible','on');
    set(hs.Push_Config_Fs,'visible','on');
    
    set(hs.Popup_Fs,'visible','on');   
    
    set(hs.Text_ConfigActual,'visible','on'); 
    set(hs.Text_FsToSet,'visible','on');    
    
    set(hs.Toggle_StartStop,'visible','on');

    
    %% CASE: Plataforma Infotronic
    if(plataforma == hs.RadioBut_Infotronic)
        % show infotronic-specific ADC stuff
        set(hs.Text_DisplayConfig,'visible','on');
        set(hs.Text_Entrada,'visible','on');
        set(hs.Popup_EA,'visible','on');
        set(hs.Push_Config_EA,'visible','on');

        % hide arduino-specific ADC stuff
%         set(hs.Text_DisplayConfig_ARDUINO,'visible','off');
%         set(hs.Text_NoArduinoConfig2,'visible','off');
    end
    
    %% CASE: Plataforma ARDUINO
    if(plataforma == hs.RadioBut_Arduino)
        % show arduino-specific ADC stuff
        set(hs.Text_DisplayConfig_ARDUINO,'visible','on');
        set(hs.Text_NoArduinoConfig2,'visible','on');
        
        
        % hide infotronic-specific ADC stuff
%         set(hs.Text_DisplayConfig,'visible','off');
%         set(hs.Text_Entrada,'visible','off');
%         set(hs.Popup_EA,'visible','off');
%         set(hs.Push_Config_EA,'visible','off');
    end
end

% update fig data
setappdata(hs.Figure,'info',info);
guidata(hObj.Parent,hs);
end