#include "clang/AST/AST.h"

#include "clang/Serialization/ASTReader.h"
#include "clang/Serialization/ASTWriter.h"

#include "clang/AST/ASTImporter.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Driver/Options.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Index/USRGeneration.h"
#include "clang/Tooling/AllTUsExecution.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Signals.h"

#include <map>
#include <memory>
#include <mutex>
#include <fstream>
#include <algorithm>
#include <execution>
#include <iostream>
#include <filesystem>

using namespace clang;
using namespace llvm;
using namespace clang::ast_matchers;
using namespace clang::tooling;


static llvm::cl::OptionCategory MyToolCategory("my-tool options");
static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);
static cl::extrahelp MoreHelp("\nMore help text...\n");


std::unique_ptr<tooling::FrontendActionFactory> createXUnusedFrontendActionFactory();
void finalize();


int main(int argc, const char ** argv)
{
  auto expectedParser = CommonOptionsParser::create(argc, argv, MyToolCategory, cl::NumOccurrencesFlag::ZeroOrMore);
  if (!expectedParser)
  {
    // Fail gracefully for unsupported options.
    llvm::errs() << expectedParser.takeError();
    return 1;
  }

  auto & optionsParser = expectedParser.get();

  const size_t limit = 9999;
  size_t i = 0;

  std::vector<std::function<void()>> tasks;

  //auto && sources = optionsParser.getSourcePathList();
  auto && sources = optionsParser.getCompilations().getAllFiles();

  //const size_t total = std::size(sources);

  //for (auto && file : sources)
  //{
  //  if (++i > limit)
  //    break;

  //  tasks.emplace_back(
  //    [i, total, file, &optionsParser]
  //    {
  //      static std::atomic_int32_t counter;
  //      std::cout << "[" << counter++ << "/" << total << "] " << file << std::endl;
  //      ClangTool Tool(optionsParser.getCompilations(), file);
  //      Tool.run(createXUnusedFrontendActionFactory().get());

  //      //auto cmd = optionsParser.getCompilations().getCompileCommands("").front();
  //      //auto ast = buildASTFromCodeWithArgs("", cmd.CommandLine);
  //      //ast.get()->getASTContext()
  //    });
  //}

  //std::for_each(std::execution::par_unseq, std::begin(tasks), std::end(tasks), [](auto && f) { f(); });

  //finalize();


  std::for_each(std::execution::par_unseq, std::begin(sources), std::end(sources),
                [&optionsParser](auto && file)
                {
                  std::cout << file << std::endl;

                  auto cmds = optionsParser.getCompilations().getCompileCommands(file);
                  if (!std::empty(cmds))
                  {
                    auto && cmd = cmds.front();
                    ClangTool Tool(optionsParser.getCompilations(), file);
                    std::vector<std::unique_ptr<ASTUnit>> ASTs;
                    Tool.buildASTs(ASTs);
                    for (auto & ast : ASTs)
                      ast->Save("A:/ast/" + std::filesystem::path{cmd.Filename}.filename().string() + ".ast");
                  }
                });

  return 0;
}
