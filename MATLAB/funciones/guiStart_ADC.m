function hs = guiStart_ADC(hs)
% hs: the structure on which I keep all handles to objects.

%% Retrieve app data
uiInfo = getappdata(hs.Figure, 'uiInfo');
BGColor = uiInfo.BGColor;
White = uiInfo.White;

%% Configuración Actual

% Configuración Actual Text
hs.strConfigActual = uicontrol(hs.Figure,'style','text');
set(hs.strConfigActual,'BackgroundColor', BGColor);
set(hs.strConfigActual,'units','normalized');
set(hs.strConfigActual,'position',[0.07 0.7 0.3 0.05]);
set(hs.strConfigActual,'string','Configuración actual:','fontsize',15);
set(hs.strConfigActual,'visible','off');

% DisplayConfig
hs.strDisplayConfig = uicontrol(hs.Figure,'style','text');
set(hs.strDisplayConfig,'BackgroundColor', BGColor);
set(hs.strDisplayConfig,'units','normalized');
set(hs.strDisplayConfig,'position',[0.4 0.695 0.4 0.06]);
set(hs.strDisplayConfig,'string','EA2, 2500 Hz.','fontsize',15);
set(hs.strDisplayConfig,'visible','off');

% DisplayConfig ARDUINO
hs.strDisplayConfig_ARDUINO = uicontrol(hs.Figure,'style','text');
set(hs.strDisplayConfig_ARDUINO,'BackgroundColor', BGColor);
set(hs.strDisplayConfig_ARDUINO,'units','normalized');
set(hs.strDisplayConfig_ARDUINO,'position',[0.4 0.695 0.4 0.06]);
set(hs.strDisplayConfig_ARDUINO,'string','Pin A0, 2500 Hz.','fontsize',15);
set(hs.strDisplayConfig_ARDUINO,'visible','off');

% DisplayConfig LPC845
hs.strDisplayConfig_LPC845 = uicontrol(hs.Figure,'style','text');
set(hs.strDisplayConfig_LPC845,'BackgroundColor', BGColor);
set(hs.strDisplayConfig_LPC845,'units','normalized');
set(hs.strDisplayConfig_LPC845,'position',[0.4 0.695 0.4 0.06]);
set(hs.strDisplayConfig_LPC845,'string','Pote, 2500 Hz.','fontsize',15);
set(hs.strDisplayConfig_LPC845,'visible','off');

%% Entrada Analógica

% Entrada Infotronic Text
hs.strEntrada = uicontrol(hs.Figure,'style','text');
set(hs.strEntrada,'BackgroundColor', BGColor);
set(hs.strEntrada,'units','normalized');
set(hs.strEntrada,'position',[0.07 0.6 0.3 0.05]);
set(hs.strEntrada,'string','Entrada del kit Infotronic:','fontsize',15);
set(hs.strEntrada,'visible','off');

% POPUP -- ADC Input Channel LPC1769 (Infotronic Entrada Analógica)
hs.Popup_EA = uicontrol('style','popupmenu');
set(hs.Popup_EA,'BackgroundColor', BGColor);
set(hs.Popup_EA,'units','normalized');
set(hs.Popup_EA,'position', [0.4 0.6 0.1 0.05]);
set(hs.Popup_EA,'string',{'EA2','EA1','EA0'},'fontsize',15);
set(hs.Popup_EA,'callback',@callback_Popup_EA);
set(hs.Popup_EA,'visible','off');

% PUSH -- Config ADC Input Channel (Entrada Analógica)
hs.Push_Config_EA = uicontrol(hs.Figure,'style','pushbutton');
set(hs.Push_Config_EA,'BackgroundColor', BGColor);
set(hs.Push_Config_EA,'units','normalized');
set(hs.Push_Config_EA,'position',[0.55 0.59 0.15 0.07]);
set(hs.Push_Config_EA,'string','Configurar','fontsize',15);
set(hs.Push_Config_EA,'callback',@callback_Configurar_EA);
set(hs.Push_Config_EA,'visible','off');

% POPUP --  ADC Input Channel LPC845
hs.Popup_EA_LPC845 = uicontrol('style','popupmenu');
set(hs.Popup_EA_LPC845,'BackgroundColor', BGColor);
set(hs.Popup_EA_LPC845,'units','normalized');
set(hs.Popup_EA_LPC845,'position', [0.4 0.6 0.1 0.05]);
set(hs.Popup_EA_LPC845,'string',{'Pote','ADC8','ADC9'},'fontsize',15);
set(hs.Popup_EA_LPC845,'callback',@callback_Popup_EA_LPC845);
set(hs.Popup_EA_LPC845,'visible','off');

hs.strNoArduinoConfig2 = uicontrol(hs.Figure,'style','text');
set(hs.strNoArduinoConfig2,'BackgroundColor', BGColor);
set(hs.strNoArduinoConfig2,'units','normalized');
set(hs.strNoArduinoConfig2,'position',[0.2 0.6 0.3 0.05]);
set(hs.strNoArduinoConfig2,'string','Arduino input pin = A0','fontsize',15);
set(hs.strNoArduinoConfig2,'visible','off');

%% Frecuencia de Muestreo

% Fs [Hz] Text
hs.strFsToSet = uicontrol(hs.Figure,'style','text');
set(hs.strFsToSet,'BackgroundColor', BGColor);
set(hs.strFsToSet,'units','normalized');
set(hs.strFsToSet,'position',[0.07 0.5 0.3 0.05]);
set(hs.strFsToSet,'string','Frecuencia de muestreo:','fontsize',15);
set(hs.strFsToSet,'visible','off');

% POPUP - Sample Rate LPC1769
hs.Popup_Fs = uicontrol('style','popupmenu');
set(hs.Popup_Fs,'BackgroundColor', BGColor);
set(hs.Popup_Fs,'units','normalized');
set(hs.Popup_Fs,'position', [0.4 0.5 0.1 0.05]);
set(hs.Popup_Fs,'string',{'2500','1600','1000','500','250','100','50','20'},'fontsize',15);
set(hs.Popup_Fs,'callback',@callback_Popup_Fs);
set(hs.Popup_Fs,'visible','off');

% POPUP - Sample Rate LPC1769
hs.Popup_Fs_LPC845 = uicontrol('style','popupmenu');
set(hs.Popup_Fs_LPC845,'BackgroundColor', BGColor);
set(hs.Popup_Fs_LPC845,'units','normalized');
set(hs.Popup_Fs_LPC845,'position', [0.4 0.5 0.1 0.05]);
set(hs.Popup_Fs_LPC845,'string',{'2500','1600','1000','500','250','100','50','20'},'fontsize',15);
set(hs.Popup_Fs_LPC845,'callback',@callback_Popup_Fs_LPC845);
set(hs.Popup_Fs_LPC845,'visible','off');

% Configurar (para setear Sample Rate) PushButton
hs.Push_Config_Fs = uicontrol(hs.Figure,'style','pushbutton');
set(hs.Push_Config_Fs,'BackgroundColor', BGColor);
set(hs.Push_Config_Fs,'units','normalized');
set(hs.Push_Config_Fs,'position',[0.55 0.49 0.15 0.07]);
set(hs.Push_Config_Fs,'string','Configurar','fontsize',15);
set(hs.Push_Config_Fs,'callback',@callback_Configurar_Fs);
set(hs.Push_Config_Fs,'visible','off');

end