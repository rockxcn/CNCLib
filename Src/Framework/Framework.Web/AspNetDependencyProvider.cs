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
using Framework.Tools.Dependency;
using Microsoft.Extensions.DependencyInjection;

namespace Framework.Web
{
    /// <summary>
    /// Implementation of IDependencyProvider that returns a single instance of LiveDependencyContainer.
    /// </summary>
    public sealed class AspNetDependencyProvider : IDependencyProvider
    {
        public AspNetDependencyProvider(IServiceCollection services)
        {
            _dependencyContainer = new AspNetDependencyContainer(services);
        }

        private readonly IDependencyContainer _dependencyContainer;

        public IDependencyContainer Container => _dependencyContainer;
    }
}
