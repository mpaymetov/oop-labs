#pragma once

std::string ExpandTemplate(std::string const& tpl, std::map<std::string, std::string> const& params);

bool ExpandTemplateFile(std::string& inputFileName, std::string& outputFileName, std::map<std::string, std::string> const& params);
