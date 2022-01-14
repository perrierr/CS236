 cmake_minimum_required(VERSION 3.16)
project(Lab_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab_1
        Parser.h
        AddAutomaton.cpp
        AddAutomaton.h
        Automaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        CommaAutomaton.cpp
        CommaAutomaton.h
        FactsAutomaton.cpp
        FactsAutomaton.h
        IDAutomaton.cpp
        IDAutomaton.h
        Left_ParenAutomaton.cpp
        Left_ParenAutomaton.h
        Lexer.cpp
        Lexer.h
        LineCommentAutomaton.cpp
        LineCommentAutomaton.h
        main.cpp
        MultilinesCommentAutomaton.cpp
        MultilinesCommentAutomaton.h
        MultiplyAutomaton.cpp
        MultiplyAutomaton.h
        PeriodAutomaton.cpp
        PeriodAutomaton.h
        Q_MarkAutomaton.cpp
        Q_MarkAutomaton.h
        QueriesAutomaton.cpp
        QueriesAutomaton.h
        Right_ParenAutomaton.cpp
        Right_ParenAutomaton.h
        RulesAutomaton.cpp
        RulesAutomaton.h
        SchemesAutomaton.cpp
        SchemesAutomaton.h
        StringAutomaton.cpp
        StringAutomaton.h
        Token.cpp
        Token.h Parser.h Rule.h Predicate.h Parameter.h DatalogProgram.h Relation.h Database.h Header.h Tuple.h Graph.h)
