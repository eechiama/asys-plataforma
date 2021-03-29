function callback_radiobutt_Plataforma(hObj, event)

% Retrieve appData
hs = guidata(hObj.Parent);
info = getappdata(hs.Figure,'info');
uiInfo = getappdata(hs.Figure,'uiInfo');

%% new selection of platform radiobuttons?
new_select = get(hs.ButGroup_Plataforma,'selectedobject');

if(new_select == hs.RadioBut_LPC1769)
    old_select = hs.RadioBut_Arduino;
end

if(new_select == hs.RadioBut_Arduino)
    old_select = hs.RadioBut_LPC1769;
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

%% Change plot ylim acording to platform adc resolution

if new_select == hs.RadioBut_Arduino
    % ylim adecuado al adc de 10bits
    set(hs.Edit_Ylim2,'string','1024','fontsize',15);
    % plot stuff
    reset_plot(hs);
    info.SamplesToRead = info.SamplesToRead_ARDUINO;
end

if ( new_select == hs.RadioBut_LPC1769 )
    % ylim adecuado al adc de 12bits
    set(hs.Edit_Ylim2,'string','4096','fontsize',15);
    % plot stuff
    reset_plot(hs);
    info.SamplesToRead = info.SamplesToRead_LPC1769;   
end

if ( new_select == hs.RadioBut_LPC845 )
    % ylim adecuado al adc de 12bits
    set(hs.Edit_Ylim2,'string','4096','fontsize',15);
    % plot stuff
    reset_plot(hs);
    info.SamplesToRead = info.SamplesToRead_LPC845;   
end

%% Change serial port string according to lpc845/lpc1769

if new_select == hs.RadioBut_LPC1769
    set(hs.Edit_Port,'string','/dev/ttyUSB0','fontsize',15);
end

if new_select == hs.RadioBut_LPC845
    set(hs.Edit_Port,'string','/dev/ttyACM0','fontsize',15);
end

%% update fig data
setappdata(hs.Figure,'info',info);
guidata(hObj.Parent,hs);
end