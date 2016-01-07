#!/usr/bin/env bash

agent_is_running() {
    if [ "$SSH_AUTH_SOCK" ]; then
        # ssh-add returns:
        #   0 = agent running, has keys
        #   1 = agent running, no keys
        #   2 = agent not running
        ssh-add -l >/dev/null 2>&1 || [ $? -eq 1 ]
    else
        false
    fi
}

agent_has_keys() {
    ssh-add -l >/dev/null 2>&1
}

find_or_start_agent() {
    # get PID if agent running
    SSH_AGENT_PID=`tasklist | grep -m 1 "ssh-agent.exe" | awk '{print $2}'`
    export SSH_AGENT_PID
    
    SSH_AUTH_SOCK=""

    if [ -z "$SSH_AGENT_PID" ]; then
        #no PID - start a new instance
        echo "Starting Agent"
        rm -rf /tmp/ssh-*
        eval "$(ssh-agent)"
    else
        #has instance, not auth sock set - try to find it
        if [ -z "$SSH_AUTH_SOCK" ]; then
            #get a matching auth sock if there is one
            if ls /tmp/ssh-*/agent* 1> /dev/null 2>&1; then
                echo "Found Agent"
                TEMP_SSH_AUTH_SOCK=`ls -1 /tmp/ssh-*/agent* | grep -m 1 "agent\."`
                SSH_AUTH_SOCK="${TEMP_SSH_AUTH_SOCK::-1}"
                export SSH_AUTH_SOCK
                unset TEMP_SSH_AUTH_SOCK
            fi
        fi
    fi
}

agent_check_start() {
    #if agent already running, with keys, 
    if ! agent_is_running; then
        find_or_start_agent
        
        # either multiple agents, or bad pids
        if ! agent_is_running; then
            # kill running instance
            echo "Unable to establish auth, restarting agent."
            cmd "/c taskkill /F /IM ssh-agent.exe"
            rm -rf /tmp/ssh-*
            find_or_start_agent
        fi
    else
        echo "Found Agent"
        echo "Agent pid $SSH_AGENT_PID"
    fi
    
    #echo "    SSH_AGENT_PID=$SSH_AGENT_PID"
    export SSH_AGENT_PID;

    #echo "    SSH_AUTH_SOCK=$SSH_AUTH_SOCK"
    export SSH_AUTH_SOCK;
}

agent_check_start

# add key if needed
if ! agent_has_keys; then
    echo ""
    ssh-add
fi
