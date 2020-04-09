function callback_radiobutt_Plataforma(hObj, event)

% Retrieve appData
hs = guidata(hObj.Parent);
info = getappdata(hs.Figure,'info');
uiInfo = getappdata(hs.Figure,'uiInfo');

%% new selection of platform radiobuttons?
new_select = get(hs.ButGroup_Plataforma,'selectedobject');

if(new_select == hs.RadioBut_Infotronic)
    old_select = hs.RadioBut_Arduino;
end

if(new_select == hs.RadioBut_Arduino)
    old_select = hs.RadioBut_Infotronic;
end

%% protection: don't change platform during sampling
if info.Sampling==1
    errordlg('No se puede cambiar la plataforma en medio del muestreo.');
    set(hs.ButGroup_Plataforma,'selectedobject',old_select);
    % update fig data
    setappdata(hs.Figure,'info',info);
    guidata(hObj.Parent,hs);
    return;
end

%% important plot stuff, changed with platform without fail.

if new_select == hs.RadioBut_Arduino
    % ylim adecuado al adc de 10bits
    set(hs.Edit_Ylim2,'string','1024','fontsize',15);
    % plot stuff
    reset_plot(hs);
    info.SamplesToRead = info.SamplesToRead_ARDUINO;
end

if new_select == hs.RadioBut_Infotronic
    % ylim adecuado al adc de 12bits
    set(hs.Edit_Ylim2,'string','4096','fontsize',15);
    % plot stuff
    reset_plot(hs);
    info.SamplesToRead = info.SamplesToRead_M3;   
end

%% update fig data
setappdata(hs.Figure,'info',info);
guidata(hObj.Parent,hs);
end

%% For OLD GUI
% Currently selected application?
% app = get(hs.ButGroup_App,'selectedobject');

%% For OLD GUI, where upon switching platform I had to show/hide lots of UI elements.
% %% CASE: APP ADQ
% if app == hs.RadioBut_ADQ
% % hide all generator stuff, both platforms
% % infotronic
% set(hs.str_pwm_NoInfotronic,'visible','off');
% % arduino
% set(hs.strSignal,'visible','off');
% set(hs.Popup_waveform,'visible','off');
% set(hs.Toggle_pwm,'visible','off');
% set(hs.strFreqDiv,'visible','off');
% set(hs.Popup_fdiv,'visible','off');
% 
%     if new_select == hs.RadioBut_Arduino
%         % hide all infotronic ADQ
%         set(hs.strDisplayConfig,'visible','off');
%         set(hs.strEntrada,'visible','off');
%         set(hs.Popup_EA,'visible','off');
%         set(hs.Push_Config_EA,'visible','off');
%         
%         % show all arduino ADQ
%         set(hs.strDisplayConfig_ARDUINO,'visible','on');
%         set(hs.strNoArduinoConfig2,'visible','on');      
%     end
%     
%     if new_select == hs.RadioBut_Infotronic
%         % hide all arduino for ADQ app
%         set(hs.strDisplayConfig_ARDUINO,'visible','off');
%         set(hs.strNoArduinoConfig2,'visible','off');        
%         
%         % show all infotronic for ADQ app
%         set(hs.strDisplayConfig,'visible','on');
%         set(hs.strEntrada,'visible','on');
%         set(hs.Popup_EA,'visible','on');
%         set(hs.Push_Config_EA,'visible','on');
%     end
% end
% 
% %% CASE: APP Generator
% if app == hs.RadioBut_Generator
%     % hide all ADQ stuff, both platforms
%     % hide all infotronic ADQ
%     set(hs.strDisplayConfig,'visible','off');
%     set(hs.strEntrada,'visible','off');
%     set(hs.Popup_EA,'visible','off');
%     set(hs.Push_Config_EA,'visible','off');
%     % hide all arduino for ADQ app
%     set(hs.strDisplayConfig_ARDUINO,'visible','off');
%     set(hs.strNoArduinoConfig2,'visible','off'); 
% 
%     if new_select == hs.RadioBut_Arduino
%         % show all arduino-generator stuff
%         set(hs.strSignal,'visible','on');
%         set(hs.Popup_waveform,'visible','on');
%         set(hs.Toggle_pwm,'visible','on');
%         set(hs.strFreqDiv,'visible','on');
%         set(hs.Popup_fdiv,'visible','on');
%         
%         % hide all infotronic-generator stuff
%         set(hs.str_pwm_NoInfotronic,'visible','off');
%     end
% 
%     if new_select == hs.RadioBut_Infotronic
%         % show all infotronic-generator stuff
%         % not implemented
%         set(hs.str_pwm_NoInfotronic,'visible','on');
%         
%         % hide all arduino generator stuff
%         set(hs.strSignal,'visible','off');
%         set(hs.Popup_waveform,'visible','off');
%         set(hs.Toggle_pwm,'visible','off');
%         set(hs.strFreqDiv,'visible','off');
%         set(hs.Popup_fdiv,'visible','off');
%     end
% 
% end

