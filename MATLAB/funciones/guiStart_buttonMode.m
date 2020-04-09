function hs = guiStart_ButtonMode(hs)
% hs: the structure on which I keep all handles to objects.

%% Retrieve app data
uiInfo = getappdata(hs.Figure, 'uiInfo');
BGColor = uiInfo.BGColor;
White = uiInfo.White;

%% Infotronic Not Implemented Text

hs.strButtons_NoInfotronic = uicontrol(hs.Figure,'style','text');
set(hs.strButtons_NoInfotronic,'BackgroundColor', BGColor);
set(hs.strButtons_NoInfotronic,'units','normalized');
set(hs.strButtons_NoInfotronic,'position',[0.62 0.35 0.3 0.2]);
set(hs.strButtons_NoInfotronic,'string',...
        'botones no implementados en el kit Infotronic','fontsize',20);
set(hs.strButtons_NoInfotronic,'visible','off');

%% Botones

% Enable / Disable
hs.Toggle_Buttons = uicontrol(hs.Figure,'style','togglebutton');
set(hs.Toggle_Buttons,'BackgroundColor', BGColor);
set(hs.Toggle_Buttons,'units','normalized');
set(hs.Toggle_Buttons,'position', [0.55 0.335 0.18 0.1]);
set(hs.Toggle_Buttons,'string','Enable','fontsize',15);
set(hs.Toggle_Buttons,'callback',@callback_toggle_buttons);
set(hs.Toggle_Buttons,'visible','off');

% POPUP waveform
hs.Popup_waveform_Buttons = uicontrol('style','popupmenu');
set(hs.Popup_waveform_Buttons,'BackgroundColor', BGColor);
set(hs.Popup_waveform_Buttons,'units','normalized');
set(hs.Popup_waveform_Buttons,'position', [0.80 0.52 0.12 0.05]);
set(hs.Popup_waveform_Buttons,'string',{'senoidal 500hz', 'rampa 245hz', 'cuadrada 500hz', 'impulso 500hz'},'fontsize',15);
set(hs.Popup_waveform_Buttons,'callback',@callback_Popup_waveform_Buttons);
set(hs.Popup_waveform_Buttons,'visible','off');

end