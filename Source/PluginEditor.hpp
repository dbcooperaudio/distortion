#pragma once

#include <JuceHeader.h>

#include "Plugin.hpp"

class PluginEditor : public juce::AudioProcessorEditor
{
public:
    PluginEditor(Plugin&);
    ~PluginEditor() = default;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
