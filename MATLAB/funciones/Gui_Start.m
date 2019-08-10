function hs = Gui_Start()
%% Figure (la main window)
hs.Figure = figure('Name','Principal');
set(hs.Figure,'units','normalized');
set(hs.Figure,'position',[0.02 0.07 0.95 0.7]);
set(hs.Figure,'color',[0.94 0.94 0.94]);
set(hs.Figure,'deletefcn',@callback_delete_figure);
set(hs.Figure,'visible','off');



%% Títulos

% Adquisidor de Señales
hs.Title = uicontrol(hs.Figure,'style','text');
set(hs.Title,'units','normalized')
set(hs.Title,'position',[0.01 0.85 0.5 0.1]);
set(hs.Title,'string','Adquisidor de Señales','fontsize',22);

% ASyS
hs.Subtitle = uicontrol(hs.Figure,'style','text');
set(hs.Subtitle,'units','normalized')
set(hs.Subtitle,'position',[0.005 0.78 0.55 0.1]);
set(hs.Subtitle,'string','Análisis de Señales y Sistemas CL2018 - UTN FRBA','fontsize',18);
set(hs.Subtitle,'fontangle','italic');





%% Selector de Plataforma

% Plataforma Text
hs.Text_Plataforma = uicontrol(hs.Figure,'style','text');
set(hs.Text_Plataforma,'units','normalized');
set(hs.Text_Plataforma,'position',[0.03 0.708 0.21 0.05]);
set(hs.Text_Plataforma,'string','Plataforma de adquisición:','fontsize',15);

% Plataforma ButtonGroup 
hs.ButGroup_Plataforma = uibuttongroup('Visible','on');
set(hs.ButGroup_Plataforma,'units', 'normalized');
set(hs.ButGroup_Plataforma,'position', [0.25 0.71 0.25 0.06]);
set(hs.ButGroup_Plataforma,'SelectionChangedFcn',@callback_PlataformaChanged);

% Plataforma RadioButton Infotronic
hs.RadioBut_Infotronic = uicontrol(hs.ButGroup_Plataforma,'Style', 'radiobutton');
set(hs.RadioBut_Infotronic,'units','normalized');
set(hs.RadioBut_Infotronic,'position',[0.05 0.25 0.55 0.5]);
set(hs.RadioBut_Infotronic,'String','kit Infotronic (Cortex M3)');
set(hs.RadioBut_Infotronic,'HandleVisibility','off');

% Plataforma RadioButton Arduino
hs.RadioBut_Arduino = uicontrol(hs.ButGroup_Plataforma,'Style', 'radiobutton');
set(hs.RadioBut_Arduino,'units','normalized');
set(hs.RadioBut_Arduino,'position',[0.65 0.25 0.3 0.5]);
set(hs.RadioBut_Arduino,'String','Arduino');
set(hs.RadioBut_Arduino,'HandleVisibility','off');

set(hs.ButGroup_Plataforma,'selectedobject',hs.RadioBut_Infotronic);







%% Puerto Serie

% SerialPort Text
hs.Text_Serial = uicontrol(hs.Figure,'style','text');
set(hs.Text_Serial,'units','normalized')
set(hs.Text_Serial,'position',[0.005 0.625 0.14 0.05]);
set(hs.Text_Serial,'string','Serial Port:','fontsize',15);

% PortName Edit
hs.Edit_Port = uicontrol(hs.Figure,'style','edit');
set(hs.Edit_Port,'units','normalized')
set(hs.Edit_Port,'position',[0.13 0.63 0.2 0.05]);
set(hs.Edit_Port,'string','/dev/ttyUSB0','fontsize',15);

% Open Serial
hs.Push_Open = uicontrol(hs.Figure,'style','pushbutton');
set(hs.Push_Open,'units','normalized');
set(hs.Push_Open,'position',[0.35 0.63 0.15 0.05]);
set(hs.Push_Open,'string','Open Serial','fontsize',15);
set(hs.Push_Open,'callback',@callback_Serial_Open);






%% SEñALES DE PRUEBA PushButtons

% Test Signal 1
hs.Push_Test1 = uicontrol(hs.Figure,'style','pushbutton');
set(hs.Push_Test1,'units','normalized')
set(hs.Push_Test1,'position',[0.05 0.55 0.1 0.06]);
set(hs.Push_Test1,'string','Test Signal 1','fontsize',13);
set(hs.Push_Test1,'callback',@callback_Test1);

% Test Signal 2
hs.Push_Test2 = uicontrol(hs.Figure,'style','pushbutton');
set(hs.Push_Test2,'units','normalized')
set(hs.Push_Test2,'position',[0.2 0.55 0.1 0.06]);
set(hs.Push_Test2,'string','Test Signal 2','fontsize',13);
set(hs.Push_Test2,'callback',@callback_Test2);

% Test Signal 3
hs.Push_Test3 = uicontrol(hs.Figure,'style','pushbutton');
set(hs.Push_Test3,'units','normalized')
set(hs.Push_Test3,'position',[0.35 0.55 0.1 0.06]);
set(hs.Push_Test3,'string','Test Signal 3','fontsize',13);
set(hs.Push_Test3,'callback',@callback_Test3);
set(hs.Push_Test3,'visible','off');






%% Guardar Muestras

% 'Guardar Muestras en' Text
hs.Text_Save = uicontrol(hs.Figure,'style','text');
set(hs.Text_Save,'units','normalized')
set(hs.Text_Save,'position',[0.026 0.47 0.18 0.05]);
set(hs.Text_Save,'string','Guardar muestras en:','fontsize',15);

% Filename
hs.Edit_File = uicontrol(hs.Figure,'style','edit');
set(hs.Edit_File,'units','normalized')
set(hs.Edit_File,'position',[0.25 0.47 0.2 0.05]);
set(hs.Edit_File,'string','~/savefile.txt','fontsize',15);





%% AVISO: Config de Arduino no implementada

hs.Text_NoArduinoConfig1 = uicontrol(hs.Figure,'style','text');
set(hs.Text_NoArduinoConfig1,'units','normalized')
set(hs.Text_NoArduinoConfig1,'position',[0.1 0.33 0.3 0.1]);
set(hs.Text_NoArduinoConfig1,'string','Fs = 500 Hz y Pin = A0','fontsize',20);
set(hs.Text_NoArduinoConfig1,'visible','off');

hs.Text_NoArduinoConfig2 = uicontrol(hs.Figure,'style','text');
set(hs.Text_NoArduinoConfig2,'units','normalized')
set(hs.Text_NoArduinoConfig2,'position',[0.1 0.224 0.3 0.15]);
set(hs.Text_NoArduinoConfig2,'string','Arduino input pin = A0','fontsize',20);
set(hs.Text_NoArduinoConfig2,'visible','off');






%% Configuración Actual

% Configuración Actual Text
hs.Text_ConfigActual = uicontrol(hs.Figure,'style','text');
set(hs.Text_ConfigActual,'units','normalized')
set(hs.Text_ConfigActual,'position',[0.03 0.39 0.17 0.05]);
set(hs.Text_ConfigActual,'string','Configuración actual:','fontsize',15);

% DisplayConfig
hs.Text_DisplayConfig = uicontrol(hs.Figure,'style','text');
set(hs.Text_DisplayConfig,'units','normalized')
set(hs.Text_DisplayConfig,'position',[0.245 0.39 0.12 0.05]);
set(hs.Text_DisplayConfig,'string','EA2, 2500 Hz.','fontsize',15);

% DisplayConfig ARDUINO
hs.Text_DisplayConfig_ARDUINO = uicontrol(hs.Figure,'style','text');
set(hs.Text_DisplayConfig_ARDUINO,'units','normalized')
set(hs.Text_DisplayConfig_ARDUINO,'position',[0.245 0.39 0.12 0.05]);
set(hs.Text_DisplayConfig_ARDUINO,'string','Pin A0, 2500 Hz.','fontsize',15);
set(hs.Text_DisplayConfig_ARDUINO,'visible','off');





%% Entrada Analógica

% Entrada Infotronic Text
hs.Text_Entrada = uicontrol(hs.Figure,'style','text');
set(hs.Text_Entrada,'units','normalized')
set(hs.Text_Entrada,'position',[0.0305 0.313 0.2 0.05]);
set(hs.Text_Entrada,'string','Entrada del kit Infotronic:','fontsize',15);

% Entradas Infotronic Popup Menu
hs.Popup_EA = uicontrol('style','popupmenu');
set(hs.Popup_EA,'units','normalized');
set(hs.Popup_EA,'position', [0.25 0.32 0.08 0.05]);
set(hs.Popup_EA,'string',{'EA2','EA1','EA0'},'fontsize',15);
set(hs.Popup_EA,'callback',@callback_Popup_EA);

% Configurar (para setear entrada del infotronic) PushButton
hs.Push_Config_EA = uicontrol(hs.Figure,'style','pushbutton');
set(hs.Push_Config_EA,'units','normalized');
set(hs.Push_Config_EA,'position',[0.35 0.32 0.15 0.05]);
set(hs.Push_Config_EA,'string','Configurar','fontsize',15);
set(hs.Push_Config_EA,'callback',@callback_Configurar_EA);







%% Frecuencia de Muestreo

% Fs [Hz] Text
hs.Text_FsToSet = uicontrol(hs.Figure,'style','text');
set(hs.Text_FsToSet,'units','normalized')
set(hs.Text_FsToSet,'position',[0.0283 0.223 0.2 0.05]);
set(hs.Text_FsToSet,'string','Frecuencia de muestreo:','fontsize',15);

% Frecuencias de Muestreo Popup Menu
hs.Popup_Fs = uicontrol('style','popupmenu');
set(hs.Popup_Fs,'units','normalized');
set(hs.Popup_Fs,'position', [0.25 0.23 0.08 0.05]);
set(hs.Popup_Fs,'string',{'2500','1600','1000','500','250','100','50','20'},'fontsize',15);
set(hs.Popup_Fs,'callback',@callback_Popup_Fs);

% Configurar (para setear Sample Rate) PushButton
hs.Push_Config_Fs = uicontrol(hs.Figure,'style','pushbutton');
set(hs.Push_Config_Fs,'units','normalized');
set(hs.Push_Config_Fs,'position',[0.35 0.23 0.15 0.05]);
set(hs.Push_Config_Fs,'string','Configurar','fontsize',15);
set(hs.Push_Config_Fs,'callback',@callback_Configurar_Fs);







%% BOTONES AGRUPADOS ABAJO

% Guardar Muestras
hs.Push_Save = uicontrol(hs.Figure,'style','pushbutton');
set(hs.Push_Save,'units','normalized')
set(hs.Push_Save,'position',[0.05 0.08 0.18 0.1]);
set(hs.Push_Save,'string','Guardar Muestras','fontsize',15);
set(hs.Push_Save,'callback',@callback_guardar_muestras);

% Start / Stop
hs.Toggle_StartStop = uicontrol(hs.Figure,'style','togglebutton');
set(hs.Toggle_StartStop,'units','normalized');
set(hs.Toggle_StartStop,'position', [0.26 0.08 0.18 0.1]);
set(hs.Toggle_StartStop,'string','Start Sampling','fontsize',15);
set(hs.Toggle_StartStop,'callback',@callback_Start_Stop);






%% Plot CONFIGS -- Xlim

% xlim Text
hs.Text_Xlim = uicontrol(hs.Figure,'style','text');
set(hs.Text_Xlim,'units','normalized')
set(hs.Text_Xlim,'position',[0.595 0.9 0.05 0.05]);
set(hs.Text_Xlim,'string','xlim:','fontsize',15);

% xlim1 Edit
hs.Edit_Xlim1 = uicontrol(hs.Figure,'style','edit');
set(hs.Edit_Xlim1,'units','normalized')
set(hs.Edit_Xlim1,'position',[0.65 0.91 0.1 0.05]);
set(hs.Edit_Xlim1,'string','0','fontsize',15);
set(hs.Edit_Xlim1,'Enable','off');

% Guión xlim Text
hs.Text_Xlim_Guion = uicontrol(hs.Figure,'style','text');
set(hs.Text_Xlim_Guion,'units','normalized')
set(hs.Text_Xlim_Guion,'position',[0.75 0.91 0.03 0.05]);
set(hs.Text_Xlim_Guion,'string','-','fontsize',15);

% xlim2 Edit
hs.Edit_Xlim2 = uicontrol(hs.Figure,'style','edit');
set(hs.Edit_Xlim2,'units','normalized')
set(hs.Edit_Xlim2,'position',[0.78 0.91 0.1 0.05]);
set(hs.Edit_Xlim2,'string','10','fontsize',15);
set(hs.Edit_Xlim2,'Enable','off');






%% Plot CONFIGS -- Ylim

% ylim Text
hs.Text_Ylim = uicontrol(hs.Figure,'style','text');
set(hs.Text_Ylim,'units','normalized')
set(hs.Text_Ylim,'position',[0.595 0.84 0.05 0.05]);
set(hs.Text_Ylim,'string','ylim:','fontsize',15);

% ylim1 Edit
hs.Edit_Ylim1 = uicontrol(hs.Figure,'style','edit');
set(hs.Edit_Ylim1,'units','normalized')
set(hs.Edit_Ylim1,'position',[0.65 0.84 0.1 0.05]);
set(hs.Edit_Ylim1,'string','0','fontsize',15);
set(hs.Edit_Ylim1,'Enable','off');

% Guión ylim Text
hs.Text_Ylim_Guion = uicontrol(hs.Figure,'style','text');
set(hs.Text_Ylim_Guion,'units','normalized')
set(hs.Text_Ylim_Guion,'position',[0.75 0.84 0.03 0.05]);
set(hs.Text_Ylim_Guion,'string','-','fontsize',15);

% ylim2 Edit
hs.Edit_Ylim2 = uicontrol(hs.Figure,'style','edit');
set(hs.Edit_Ylim2,'units','normalized')
set(hs.Edit_Ylim2,'position',[0.78 0.84 0.1 0.05]);
set(hs.Edit_Ylim2,'string','4096','fontsize',15);
set(hs.Edit_Ylim2,'Enable','off');







%% Plot CONFIGS -- CHECKBOXES

% Real-Time Checkbox
hs.Checkbox_RTP = uicontrol(hs.Figure,'style','checkbox');
set(hs.Checkbox_RTP,'units','normalized')
set(hs.Checkbox_RTP,'position',[0.55 0.77 0.14 0.05]);
set(hs.Checkbox_RTP,'string','  "Tiempo Real"','fontsize',15);
set(hs.Checkbox_RTP,'value',1);
set(hs.Checkbox_RTP,'callback',@callback_PlotOptionsCheck);

% Axis Tight Checkbox
hs.Checkbox_Tight = uicontrol(hs.Figure,'style','checkbox');
set(hs.Checkbox_Tight,'units','normalized')
set(hs.Checkbox_Tight,'position',[0.7 0.77 0.14 0.05]);
set(hs.Checkbox_Tight,'string','  Axis Tight','fontsize',15);
set(hs.Checkbox_Tight,'value',1);
set(hs.Checkbox_Tight,'callback',@callback_PlotOptionsCheck);

% Grid Checkbox
hs.Checkbox_Grid = uicontrol(hs.Figure,'style','checkbox');
set(hs.Checkbox_Grid,'units','normalized')
set(hs.Checkbox_Grid,'position',[0.825 0.77 0.14 0.05]);
set(hs.Checkbox_Grid,'string','  Grid','fontsize',15);
set(hs.Checkbox_Grid,'value',1);







%% PLOT Gráfico y Replot

% Axes
hs.Axis = axes();
set(hs.Axis,'units','normalized');
set(hs.Axis,'position', [0.545 0.11 0.44 0.6]);
set(hs.Axis,'box','on');
set(hs.Axis,'color','white');
reset_plot(hs);

% Update Plot PushButton
hs.Push_UpdatePlot = uicontrol(hs.Figure,'style','pushbutton');
set(hs.Push_UpdatePlot,'units','normalized');
set(hs.Push_UpdatePlot,'position',[0.895 0.765 0.08 0.2]);
set(hs.Push_UpdatePlot,'string','Re-plot','fontsize',15);
set(hs.Push_UpdatePlot,'callback',@callback_update_plot);
set(hs.Push_UpdatePlot,'Enable','off');





%% Utilizados durante el desarrollo, y debug

% Remaining Bytes
% hs.Text_Remaining = uicontrol(hs.Figure,'style','text');
% set(hs.Text_Remaining,'units','normalized')
% set(hs.Text_Remaining,'position',[0.44 0.25 0.07 0.08]);
% set(hs.Text_Remaining,'string','-','fontsize',20);

% Check Bytes
% hs.Push_CheckBytes = uicontrol(hs.Figure,'style','pushbutton');
% set(hs.Push_CheckBytes,'units','normalized')
% set(hs.Push_CheckBytes,'position',[0.26 0.25 0.18 0.1]);
% set(hs.Push_CheckBytes,'string','Check Bytes','fontsize',15);
% set(hs.Push_CheckBytes,'callback',@callback_check_bytes);

%% Hago visible la figura
set(hs.Figure,'visible','on');

end