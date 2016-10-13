﻿////////////////////////////////////////////////////////
/*
  This file is part of CNCLib - A library for stepper motors.

  Copyright (c) 2013-2016 Herbert Aitenbichler

  CNCLib is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  CNCLib is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  http://www.gnu.org/licenses/
*/

using System;
using System.Windows;
using System.Windows.Controls;
using CNCLib.Wpf.ViewModels;

namespace CNCLib.Wpf.Views
{
	/// <summary>
	/// Interaction logic for SetupPage.xaml
	/// </summary>
	public partial class SetupPage : Page
	{
		public SetupPage()
		{
			InitializeComponent();

			var vm = DataContext as SetupWindowViewModel;

			if (vm.EditMachine == null)
			{
				vm.EditMachine = new Action<int>((mID) =>
				{
					var dlg = new MachineView();
					var vmdlg = dlg.DataContext as MachineViewModel;
					vmdlg.LoadMachine(mID);
					dlg.ShowDialog();
				});
			}

			if (vm.EditJoystick == null)
			{
				vm.EditJoystick = new Action(() =>
				{
					var dlg = new JoystickView();
					var vmdlg = dlg.DataContext as JoystickView;
					dlg.ShowDialog();
				});
			}

			if (vm.MessageBox == null)
			{
				vm.MessageBox = new Func<string, string, MessageBoxButton, MessageBoxImage, MessageBoxResult>((messageBoxText, caption, button, icon) =>
				{
					return MessageBox.Show(messageBoxText, caption, button, icon);
				});
			}
		}
	}
}
