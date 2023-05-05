/*
Copyright Contributors to the dnf5 project.

This file is part of libdnf: https://github.com/rpm-software-management/libdnf/

Dnf5 is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 2.1 of the License, or
(at your option) any later version.

Libdnf is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with libdnf.  If not, see <https://www.gnu.org/licenses/>.
*/


#include "dnf5/shared_options.hpp"


namespace dnf5 {


void create_allow_downgrade_options(dnf5::Command & command) {
    auto * solver_options = command.get_context().get_argument_parser().add_new_group("solver_options");
    solver_options->set_header("Solver Options:");
    auto * parser_command = command.get_argument_parser_command();
    parser_command->register_group(solver_options);

    auto & parser = command.get_context().get_argument_parser();
    auto allow_downgrade = parser.add_new_named_arg("allow-downgrade");
    allow_downgrade->set_long_name("allow-downgrade");
    allow_downgrade->set_description("Allow downgrade of dependencies for resolve of requested operation");
    allow_downgrade->set_const_value("true");
    allow_downgrade->link_value(&command.get_context().base.get_config().get_allow_downgrade_option());
    parser_command->register_named_arg(allow_downgrade);

    auto no_allow_downgrade = parser.add_new_named_arg("no-allow-downgrade");
    no_allow_downgrade->set_long_name("no-allow-downgrade");
    no_allow_downgrade->set_description("Disable downgrade of dependencies for resolve of requested operation");
    no_allow_downgrade->set_const_value("false");
    no_allow_downgrade->link_value(&command.get_context().base.get_config().get_allow_downgrade_option());
    parser_command->register_named_arg(no_allow_downgrade);

    allow_downgrade->add_conflict_argument(*no_allow_downgrade);
}


}  // namespace dnf5
