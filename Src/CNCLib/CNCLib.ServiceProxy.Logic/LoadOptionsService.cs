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
using System.Collections.Generic;
using System.Threading.Tasks;
using CNCLib.Logic.Contracts;
using CNCLib.Logic.Contracts.DTO;
using Framework.Tools;

namespace CNCLib.ServiceProxy.Logic
{
    public class LoadOptionsService : DisposeWrapper, ILoadOptionsService
	{
        public LoadOptionsService(ILoadOptionsController controller)
        {
            _controller = controller ?? throw new ArgumentNullException();
        }

        readonly ILoadOptionsController _controller;

		public async Task<int> Add(LoadOptions value)
		{
			return await _controller.Add(value);
		}

		public async Task Delete(LoadOptions value)
		{
			await _controller.Delete(value);
		}

		public async Task<LoadOptions> Get(int id)
		{
			return await _controller.Get(id);
		}

		public async Task<IEnumerable<LoadOptions>> GetAll()
		{
			return await _controller.GetAll();
		}

		public async Task<int> Update(LoadOptions value)
		{
			return await _controller.Update(value);
		}

        #region IDisposable Support

        protected override void DisposeManaged()
        {
        }

        #endregion

    }
}
