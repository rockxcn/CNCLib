﻿////////////////////////////////////////////////////////
/*
  This file is part of CNCLib - A library for stepper motors.

  Copyright (c) 2013-2018 Herbert Aitenbichler

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
using System.IO;
using System.Windows;
using System.Windows.Controls;
using Framework.Wpf.ViewModels;

namespace Framework.Wpf.View
{
    public static class BaseViewModelExtensions
    {
        public static void DefaulInitForBaseViewModel(this BaseViewModel vm)
        {
            if (vm.MessageBox == null)
            {
                vm.MessageBox = (messageBoxText, caption, button, icon) =>
                {
                    return MessageBox.Show(messageBoxText, caption, button, icon);
                };
            }

            if (vm.BrowseFileNameFunc == null)
            {
                vm.BrowseFileNameFunc = (filename, savefile) =>
                {
                    Microsoft.Win32.FileDialog dlg;
                    if (savefile)
                    {
                        dlg = new Microsoft.Win32.SaveFileDialog();
                    }
                    else
                    {
                        dlg = new Microsoft.Win32.OpenFileDialog();
                    }
                    dlg.FileName = filename;
                    string dir = Path.GetDirectoryName(filename);
                    if (!string.IsNullOrEmpty(dir))
                    {
                        dlg.InitialDirectory = dir;
                        dlg.FileName = Path.GetFileName(filename);
                    }

                    if ((dlg.ShowDialog() ?? false))
                    {
                        return dlg.FileName;
                    }
                    return null;
                };
            }
        }

        public static void DefaulInitForBaseViewModel(this Window view)
        {
            var vm = view.DataContext as BaseViewModel;

            if (vm != null)
            {
                vm.DefaulInitForBaseViewModel();

                var closeAction = new Action(() => view.Close());
                var dialogOkAction = new Action(() => { view.DialogResult = true; view.Close(); });
                var dialogCancelAction = new Action(() => { view.DialogResult = false; view.Close(); });
                var loadedEvent = new RoutedEventHandler(async (v, e) =>
                {
                    var vmm = view.DataContext as BaseViewModel;
                    if (vmm != null) await vmm.Loaded();
                });

                RoutedEventHandler unloadedEvent=null;

                unloadedEvent = (v, e) =>
                {
                    vm.CloseAction = null;
                    vm.DialogOKAction = null;
                    vm.DialogCancelAction = null;
                    view.Loaded -= loadedEvent;
                    view.Unloaded -= unloadedEvent;
                };

                vm.CloseAction = closeAction;
                vm.DialogOKAction = dialogOkAction;
                vm.DialogCancelAction = dialogCancelAction;

                view.Loaded += loadedEvent;
                view.Unloaded += unloadedEvent;
            }
        }
        public static void DefaulInitForBaseViewModel(this Page view)
        {
            var vm = view.DataContext as BaseViewModel;

            if (vm != null)
            {
                vm.DefaulInitForBaseViewModel();

                view.Loaded += async (v, e) =>
                {
                    var vmm = view.DataContext as BaseViewModel;
                    if (vmm != null) await vmm.Loaded();
                };
            }
        }
    }
}
