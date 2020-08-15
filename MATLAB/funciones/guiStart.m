function hs = guiStart()

%% Screen size information
%   Get user screen size
SC = get(0, 'ScreenSize');
MaxMonitorX = SC(3);
MaxMonitorY = SC(4);

%   Set the figure window size values
MainFigScale = .8;
MaxWindowX = round(MaxMonitorX*MainFigScale);
MaxWindowY = round(MaxMonitorY*MainFigScale);

%   Split the remaining space in 2
%   This are the coordinates for a centered figure
XBorder = (MaxMonitorX-MaxWindowX)/2;
YBorder = (MaxMonitorY-MaxWindowY)/3;

%   Set the color varables.  
White = [1  1  1];            % White - Selected tab color     
BGColor = .9*White;           % Light Grey - Background color


%% TABs Config
%   Set Number of tabs and tab labels
NumberOfTabs = 4;               % Number of tabs to be generated
TabLabels = {'Conexión'; 'ADC'; 'Generador Periódico (PWM)'; 'Plot'};
if size(TabLabels,1) ~= NumberOfTabs
    errordlg('Number of tabs and tab labels must be the same','Setup Error');
    return
end

TabOffset = 0;              % This value offsets the tabs inside the figure.
ButtonHeight = 40;
PanelWidth = MaxWindowX-2*TabOffset+4;
PanelHeight = MaxWindowY-ButtonHeight-2*TabOffset;
ButtonWidth = round((PanelWidth-NumberOfTabs)/NumberOfTabs);


%% Figure (main window)
hs.Figure = figure('Name','ASyS ADQ');
set(hs.Figure,'menubar','none');
set(hs.Figure,'toolbar','figure');
set(hs.Figure,'units','pixels');
set(hs.Figure,'Position', [XBorder, YBorder, MaxWindowX, MaxWindowY]);
set(hs.Figure,'resize', 'off');
set(hs.Figure,'NumberTitle', 'off');
set(hs.Figure,'DockControl', 'off');
set(hs.Figure,'color', White);
set(hs.Figure,'visible','off');
set(hs.Figure,'deletefcn',@callback_delete_figure);


%%  TABs array for handles
%   rows are for tabs for each tab handles
%   columns (3) are for:    uipanel handles, pushbutton handles, and tab labels.
TabHandles = cell(NumberOfTabs,3);
TabHandles(:,3) = TabLabels(:,1);

        
%% TABs init.
for TabNumber = 1:NumberOfTabs
% create a UIPanel   
    TabHandles{TabNumber,1} = uipanel('Units', 'pixels', ...
        'Visible',  'off', ...
        'Backgroundcolor', White, ...
        'BorderWidth',1, ...
        'Position', [TabOffset, TabOffset, PanelWidth, PanelHeight]);
% create a selection pushbutton
    TabHandles{TabNumber,2} = uicontrol('Style', 'pushbutton',...
        'Units', 'pixels', ...
        'BackgroundColor', BGColor, ...
        'Position', [TabOffset+(TabNumber-1)*ButtonWidth PanelHeight+TabOffset...
            ButtonWidth ButtonHeight], ...          
        'String', TabLabels{TabNumber,1},...
        'HorizontalAlignment', 'center',...
        'FontName', 'arial',...
        'FontWeight', 'bold',...
        'FontSize', 10);
end


%%   TABs callback assignament.
%   All callbacks go to the same function with the additional argument being the Tab number
for CountTabs = 1:NumberOfTabs
    set(TabHandles{CountTabs,2}, 'callback', ...
        {@callback_TabSelect, CountTabs});
end

% Save this array of handles on the handles structure I use
hs.TabHandles = TabHandles;


%% Initialize tab on selection 1
% selection is made to have white background for the pushButton
% and unselected are greyed

for TabCount = 1:NumberOfTabs
    set(TabHandles{TabCount,1}, 'Visible', 'off');
    set(TabHandles{TabCount,2}, 'BackgroundColor', BGColor);
end

set(TabHandles{1,1}, 'Visible', 'on');        
set(TabHandles{1,2}, 'BackgroundColor', White);


%% Títulos

% Adquisidor de Señales
hs.strTitle = uicontrol(hs.Figure,'style','text');
set(hs.strTitle,'BackgroundColor', BGColor);
set(hs.strTitle,'units','normalized');
set(hs.strTitle,'position',[0.05, 0.85, 0.3, 0.05]);
set(hs.strTitle,'string','Adquisidor de Señales','fontsize',20);
set(hs.strTitle,'visible','on');

% ASyS
hs.strSubtitle = uicontrol(hs.Figure,'style','text');
set(hs.strSubtitle,'BackgroundColor', BGColor);
set(hs.strSubtitle,'units','normalized');
set(hs.strSubtitle,'position',[0.38, 0.85, 0.6, 0.05]);
set(hs.strSubtitle,'string','Análisis de Señales y Sistemas CL2018 UTN FRBA','fontsize',18);
set(hs.strSubtitle,'fontangle','italic');
set(hs.strSubtitle,'visible','on');


%% Save information to app data
uiInfo.White = White;
uiInfo.BGColor = BGColor;
uiInfo.NumberOfTabs = NumberOfTabs;
uiInfo.TabLabels = TabLabels;
uiInfo.SelectedTab = uiInfo.TabLabels{1,1}; % Upon opening, selected tab is defaulted to the first one. 'Conexión'
setappdata(hs.Figure,'uiInfo',uiInfo);

%% Call other GUI initialization functions
hs = guiStart_Conexion(hs);
hs = guiStart_ADC(hs);
hs = guiStart_Plot(hs);
hs = guiStart_Generator(hs);
hs = guiStart_buttonMode(hs);

%% Hago visible la figura
set(hs.Figure,'visible','on');










%% Selector de Aplicación

% Aplicación Text
hs.strApp = uicontrol(hs.Figure,'style','text');
set(hs.strApp,'units','normalized');
set(hs.strApp,'position',[0.65 0.83 0.22 0.05]);
set(hs.strApp,'string','Aplicación','fontsize',17);
set(hs.strApp,'visible','off');

% Aplicación ButtonGroup 
hs.ButGroup_App = uibuttongroup('Visible','on');
set(hs.ButGroup_App,'units', 'normalized');
set(hs.ButGroup_App,'position', [0.59 0.76 0.32 0.06]);
set(hs.ButGroup_App,'SelectionChangedFcn',@callback_radiobutt_App);
set(hs.ButGroup_App,'visible','off');

% Aplicación RadioButton Adquisidor (ADC)
hs.RadioBut_ADQ = uicontrol(hs.ButGroup_App,'Style', 'radiobutton');
set(hs.RadioBut_ADQ,'units','normalized');
set(hs.RadioBut_ADQ,'position',[0.025 0.25 0.45 0.5]);
set(hs.RadioBut_ADQ,'String','Adquisidor (ADC)');
set(hs.RadioBut_ADQ,'HandleVisibility','off');

% Aplicación RadioButton Generador (PWM)
hs.RadioBut_Generator = uicontrol(hs.ButGroup_App,'Style', 'radiobutton');
set(hs.RadioBut_Generator,'units','normalized');
set(hs.RadioBut_Generator,'position',[0.37 0.25 0.45 0.5]);
set(hs.RadioBut_Generator,'String','Generador (PWM)');
set(hs.RadioBut_Generator,'HandleVisibility','off');

% Aplicación RadioButton Botones
hs.RadioBut_Buttons = uicontrol(hs.ButGroup_App,'Style', 'radiobutton');
set(hs.RadioBut_Buttons,'units','normalized');
set(hs.RadioBut_Buttons,'position',[0.75 0.25 0.45 0.5]);
set(hs.RadioBut_Buttons,'String','Botones');
set(hs.RadioBut_Buttons,'HandleVisibility','off');

set(hs.ButGroup_App,'selectedobject',hs.RadioBut_ADQ);





















end

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


% %% SEñALES DE PRUEBA PushButtons
% 
% % Test Signal 2
% hs.Push_Test2 = uicontrol(hs.Figure,'style','pushbutton');
% set(hs.Push_Test2,'units','normalized');
% set(hs.Push_Test2,'position',[0.2 0.55 0.1 0.06]);
% set(hs.Push_Test2,'string','Test Signal 2','fontsize',13);
% set(hs.Push_Test2,'callback',@callback_Test2);
% set(hs.Push_Test2,'visible','off');
% 
% % Test Signal 3
% hs.Push_Test3 = uicontrol(hs.Figure,'style','pushbutton');
% set(hs.Push_Test3,'units','normalized');
% set(hs.Push_Test3,'position',[0.35 0.55 0.1 0.06]);
% set(hs.Push_Test3,'string','Test Signal 3','fontsize',13);
% set(hs.Push_Test3,'callback',@callback_Test3);
% set(hs.Push_Test3,'visible','off');
