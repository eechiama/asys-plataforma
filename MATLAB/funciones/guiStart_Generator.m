function hs = guiStart_Generator(hs)
% hs: the structure on which I keep all handles to objects.

%% Retrieve app data
uiInfo = getappdata(hs.Figure, 'uiInfo');
BGColor = uiInfo.BGColor;
White = uiInfo.White;

%% Infotronic Not Implemented Text

hs.str_pwm_NoInfotronic = uicontrol(hs.Figure,'style','text');
set(hs.str_pwm_NoInfotronic,'BackgroundColor', BGColor);
set(hs.str_pwm_NoInfotronic,'units','normalized');
set(hs.str_pwm_NoInfotronic,'position',[0.07 0.45 0.7 0.1]);
set(hs.str_pwm_NoInfotronic,'string',...
        'generador no implementado para LPC1769 / LPC845','fontsize',22);
set(hs.str_pwm_NoInfotronic,'visible','off');

%% Arduino waveform

% Waveform text
hs.strSignal = uicontrol(hs.Figure,'style','text');
set(hs.strSignal,'BackgroundColor', BGColor);
set(hs.strSignal,'units','normalized');
set(hs.strSignal,'position',[0.07 0.7 0.3 0.05]);
set(hs.strSignal,'string','Forma de la señal modulada:','fontsize',15);
set(hs.strSignal,'visible','off');

% POPUP waveform
hs.Popup_waveform = uicontrol('style','popupmenu');
set(hs.Popup_waveform,'BackgroundColor', BGColor);
set(hs.Popup_waveform,'units','normalized');
set(hs.Popup_waveform,'position', [0.4 0.695 0.2 0.06]);
set(hs.Popup_waveform,'string',{'rampa 245hz','logic high','senoidal 500hz','cuadrada 500hz','ECG2', 'impulso 500hz'},'fontsize',15);
set(hs.Popup_waveform,'callback',@callback_Popup_waveform);
set(hs.Popup_waveform,'visible','off');

%% Arduino frequency divider

% frequency divider text
hs.strFreqDiv = uicontrol(hs.Figure,'style','text');
set(hs.strFreqDiv,'BackgroundColor', BGColor);
set(hs.strFreqDiv,'units','normalized');
set(hs.strFreqDiv,'position',[0.07 0.6 0.3 0.05]);
set(hs.strFreqDiv,'string','Divisor de frecuencia:','fontsize',15);
set(hs.strFreqDiv,'visible','off');

% POPUP divider values
hs.Popup_fdiv = uicontrol('style','popupmenu');
set(hs.Popup_fdiv,'BackgroundColor', BGColor);
set(hs.Popup_fdiv,'units','normalized');
set(hs.Popup_fdiv,'position', [0.4 0.6 0.1 0.05] );
set(hs.Popup_fdiv,'string',{'1','2','4','5','10','20','25','50','100','500'},'fontsize',15);
set(hs.Popup_fdiv,'callback',@callback_Popup_fdiv);
set(hs.Popup_fdiv,'visible','off');
