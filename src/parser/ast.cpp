#include <utility>
#include <string>
#include <fstream>
#include <iostream>

#include "ast.h"

// ========= AstNode ========

std::string AstNode::get_node_dot()const{
    std::string str;
    return str+token.second+"[label="+token.first+"];\n";
}

// ========= Ast ========
void Ast::output_graphviz(const std::string &filename)const{
    std::ofstream out(filename);
    if (!out.is_open()){
        std::cout << filename << " not found!" << std::endl;
        exit(1);
    }
    out << "digraph Ast{\n";
    auto str = get_graphviz(root);
    std::cout << str << std::endl;
    out.write(str.c_str(), str.length());
    out << "}";
}

std::string Ast::get_graphviz(std::shared_ptr<AstNode> ptr)const{
    if (ptr == nullptr)
        return "";
    auto str = ptr->get_node_dot();
    for (auto p :ptr->children) {
    std::cout << p->token.first << std::endl;
        str += ptr->token.second +"->"+p->token.second+"\n";
        str += get_graphviz(p);
    }
    return str;
}