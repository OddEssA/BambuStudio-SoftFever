//
//  MediaPlayCtrl.h
//  libslic3r_gui
//
//  Created by cmguo on 2021/12/7.
//

#ifndef MediaPlayCtrl_h
#define MediaPlayCtrl_h

#include "wxMediaCtrl2.h"

#include <wx/panel.h>

#include <boost/thread.hpp>
#include <boost/thread/condition_variable.hpp>

#include <deque>

class Button;
class Label;

namespace Slic3r {

class MachineObject;

namespace GUI {

class MediaPlayCtrl : public wxPanel
{
public:
    MediaPlayCtrl(wxWindow *parent, wxMediaCtrl2 *media_ctrl, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize);

    ~MediaPlayCtrl();

    void SetMachineObject(MachineObject * obj);

protected:
    void onStateChanged(wxMediaEvent & event);

    void Play();

    void Stop();

    void TogglePlay();

    void SetStatus(wxString const & msg);

private:
    void media_proc();

private:
    static constexpr wxMediaState MEDIASTATE_IDLE = (wxMediaState) 3;
    static constexpr wxMediaState MEDIASTATE_INITIALIZING = (wxMediaState) 4;
    static constexpr wxMediaState MEDIASTATE_LOADING = (wxMediaState) 5;
    static constexpr wxMediaState MEDIASTATE_BUFFERING = (wxMediaState) 6;

    wxMediaCtrl2 * m_media_ctrl;
    wxMediaState m_last_state = MEDIASTATE_IDLE;
    std::string m_machine;
    wxString m_url;
    
    std::deque<wxString> m_tasks;
    boost::mutex m_mutex;
    boost::condition_variable m_cond;
    boost::thread m_thread;

    int m_failed_retry = 0;
    int m_failed_code = 0;
    wxDateTime m_next_retry;

    ::Button * m_button_play;
    ::Label * m_label_status;
};

}}

#endif /* MediaPlayCtrl_h */