clear all;
clc;

%   Set Number of tabs and tab labels.  Make sure the number of tab labels
%   match the HumberOfTabs setting.
        NumberOfTabs = 6;               % Number of tabs to be generated
        TabLabels = {'Open Image File'; 'Image'; 'Tab3'; 'Tab4'; 'Tab 5'; 'Tab 6'};
        if size(TabLabels,1) ~= NumberOfTabs
            errordlg('Number of tabs and tab labels must be the same','Setup Error');
            return
        end

%   Get user screen size
        SC = get(0, 'ScreenSize');
        MaxMonitorX = SC(3);
        MaxMonitorY = SC(4);
        
%   Set the figure window size values
        MainFigScale = .75;
        MaxWindowX = round(MaxMonitorX*MainFigScale);
        MaxWindowY = round(MaxMonitorY*MainFigScale);
        
%   Split the remaining space in 2
%   This are the coordinates for a centered figure
        XBorder = (MaxMonitorX-MaxWindowX)/2;
        YBorder = (MaxMonitorY-MaxWindowY)/3;
        
 %   Set the color varables.  
        White = [1  1  1];            % White - Selected tab color     
        BGColor = .9*White;           % Light Grey - Background color


        

        TabOffset = 0;              % This value offsets the tabs inside the figure.
        ButtonHeight = 40;
        PanelWidth = MaxWindowX-2*TabOffset+4;
        PanelHeight = MaxWindowY-ButtonHeight-2*TabOffset;
        ButtonWidth = round((PanelWidth-NumberOfTabs)/NumberOfTabs);

            
%%   Create a figure for the tabs
        hTabFig = figure(...
            'Units', 'pixels',...
            'MenuBar', 'none',...
            'Toolbar', 'figure',...
            'Position',[ XBorder, YBorder, MaxWindowX, MaxWindowY ],...
            'Resize', 'off',...
            'Name', 'Tab Demo',...
            'NumberTitle', 'off',...
            'DockControls', 'off',...
            'Color', White);

        
%%   Define a cell array for panel and pushbutton handles, pushbuttons labels and other data
    %   rows are for each tab + two additional rows for other data
    %   columns are uipanel handles, selection pushbutton handles, and tab label strings - 3 columns.
            TabHandles = cell(NumberOfTabs,3);
            TabHandles(:,3) = TabLabels(:,1);
    %   Add additional rows for other data
            TabHandles{NumberOfTabs+1,1} = hTabFig;         % Main figure handle
            TabHandles{NumberOfTabs+1,2} = PanelWidth;      % Width of tab panel
            TabHandles{NumberOfTabs+1,3} = PanelHeight;     % Height of tab panel
            TabHandles{NumberOfTabs+2,1} = 0;               % Handle to default tab 2 content(set later)
            TabHandles{NumberOfTabs+2,2} = White;           % Selected tab Color
            TabHandles{NumberOfTabs+2,3} = BGColor;         % Background color

            
%%   Build the Tabs
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
        
     
%%   Define the callbacks for the Tab Buttons
%   All callbacks go to the same function with the additional argument being the Tab number
        for CountTabs = 1:NumberOfTabs
            set(TabHandles{CountTabs,2}, 'callback', ...
                {@callback_TabSelect, CountTabs});
        end
        
        
%%   Callback for Tab Selection
function callback_TabSelect(~,~,SelectedTab)
%   All tab selection pushbuttons are greyed out and uipanels are set to
%   visible off, then the selected panel is made visible and it's selection
%   pushbutton is highlighted.
    %   Set up some varables
        TabHandles = guidata(gcf);
        NumberOfTabs = size(TabHandles,1)-2;
        White = TabHandles{NumberOfTabs+2,2};            % White      
        BGColor = TabHandles{NumberOfTabs+2,3};          % Light Grey
        
    %   Turn all tabs off
        for TabCount = 1:NumberOfTabs
            set(TabHandles{TabCount,1}, 'Visible', 'off');
            set(TabHandles{TabCount,2}, 'BackgroundColor', BGColor);
        end
        
    %   Enable the selected tab
        set(TabHandles{SelectedTab,1}, 'Visible', 'on');        
        set(TabHandles{SelectedTab,2}, 'BackgroundColor', White);
end