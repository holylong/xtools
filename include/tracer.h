#ifndef _SKILL_TRACER_H
#define _SKILL_TRACER_H

#include <iostream>
#include <ostream>

static const int skdebug = 0;

#ifdef _WIN32
#if !defined(__PRETTY_FUNCTION__)
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif
#endif

namespace halgo{
    class Channel{
        friend class Trace;
        std::ostream* trace_file;

        public:
            Channel(std::ostream* o = &std::cout):trace_file(o){}
            void reset(std::ostream* o){trace_file = o;}

        static Channel *Instance(){
            static Channel instance;
            return &instance;
        }
    };

    class Trace{
        public:
        Trace(const char *s, Channel* c){
            if(skdebug){
                name = s;
                cl = c;
                if(cl->trace_file)*cl->trace_file << name << " enter" << std::endl;
            }
        }

        ~Trace()
        {
            if(skdebug){
                if(cl->trace_file){
                    *cl->trace_file << name << " exit" << std::endl;
                }
            }
        }

        private:
            const char *name;
            Channel    *cl;
    };
}

#define SK_TRACE_FUNC() halgo::Trace MY_TRACER(__PRETTY_FUNCTION__, halgo::Channel::Instance());

#endif //_SKILL_TRACER_H
