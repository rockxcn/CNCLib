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

using System.Threading.Tasks;
using Framework.Tools.Pattern;

namespace CNCLib.Repository.Contracts
{
	public interface IUserRepository: IBaseRepository
	{
		Task<Entities.User[]> GetUsers();
		Task<Entities.User> GetUser(int id);
        Task<Entities.User> GetUser(string username);
        Task Delete(Entities.User u);
		Task Store(Entities.User u);
	}
}
