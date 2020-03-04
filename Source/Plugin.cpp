#include "Plugin.hpp"
#include "PluginEditor.hpp"


const juce::StringRef Plugin::ParamIds::Input       ("input");
const juce::StringRef Plugin::ParamIds::Output      ("output");
const juce::StringRef Plugin::ParamIds::Brightness  ("brightness");
const juce::StringRef Plugin::ParamIds::Drive       ("drive");
const juce::StringRef Plugin::ParamIds::Overdrive   ("overdrive");
const juce::StringRef Plugin::ParamIds::InputMeter  ("input_meter");
const juce::StringRef Plugin::ParamIds::OutputMeter ("output_meter");


Plugin::Plugin() : dB::Plugin(createDefaultIO(), createParameters())
{
    params.input       = state.getRawParameterValue(ParamIds::Input);
    params.output      = state.getRawParameterValue(ParamIds::Output);
    params.brightness  = state.getRawParameterValue(ParamIds::Brightness);
    params.drive       = state.getRawParameterValue(ParamIds::Drive);
    params.overdrive   = state.getRawParameterValue(ParamIds::Overdrive);

    params.inputMeter  = state.getParameter(ParamIds::InputMeter);
    params.outputMeter = state.getParameter(ParamIds::OutputMeter);
}


juce::StringArray
Plugin::getAlternateDisplayNames() const
{
    return {JucePlugin_Name};
}


juce::AudioProcessor::BusesProperties
Plugin::createDefaultIO()
{
    return BusesProperties()
        .withInput ("Input",  juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true);
}


juce::AudioProcessorValueTreeState::ParameterLayout
Plugin::createParameters()
{
    return {
        std::make_unique<juce::AudioParameterFloat>(
            ParamIds::Input, "Input",
            juce::NormalisableRange<float>(-10.0f, 10.0f), 0.0f,
            "dB",
            juce::AudioProcessorParameter::inputGain
        ),
        std::make_unique<juce::AudioParameterFloat>(
            ParamIds::Output, "Output",
            juce::NormalisableRange<float>(-10.0f, 10.0f), 0.0f,
            "dB",
            juce::AudioProcessorParameter::outputGain
        ),
        std::make_unique<juce::AudioParameterFloat>(
            ParamIds::Brightness, "Brightness",
            juce::NormalisableRange<float>(0.0f, 1.0f), 0.5f,
            "%"
        ),
        std::make_unique<juce::AudioParameterFloat>(
            ParamIds::Drive, "Drive",
            juce::NormalisableRange<float>(0.0f, 1.0f), 0.0f,
            "%"
        ),
        std::make_unique<juce::AudioParameterBool>(
            ParamIds::Overdrive, "Overdrive",
            false
        ),
        std::make_unique<juce::AudioParameterFloat>(
            ParamIds::InputMeter, "Input Meter",
            juce::NormalisableRange<float>(0.0f, 1.0f), 0.0f,
            "",
            juce::AudioProcessorParameter::inputMeter
        ),
        std::make_unique<juce::AudioParameterFloat>(
            ParamIds::OutputMeter, "Output Meter",
            juce::NormalisableRange<float>(0.0f, 1.0f), 0.0f,
            "",
            juce::AudioProcessorParameter::outputMeter
        )
    };
}


void
Plugin::prepareToPlay(
    const double /* sampleRate      */,
    const int    /* samplesPerBlock */)
{

}


bool
Plugin::isBusesLayoutSupported(
    const BusesLayout& layouts) const
{
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
    &&  layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
}


void
Plugin::processBlock(
    juce::AudioBuffer<float>& buffer,
    juce::MidiBuffer& /* midiMessages */)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    buffer.applyGain(juce::Decibels::decibelsToGain(params.input->load()));

    // ...

    buffer.applyGain(juce::Decibels::decibelsToGain(params.output->load()));
}


void
Plugin::processBlockBypassed(
    juce::AudioBuffer<float>& buffer,
    juce::MidiBuffer& midiMessages)
{
    processBlock(buffer, midiMessages);
}


bool
Plugin::hasEditor() const
{
    return true;
}


juce::AudioProcessorEditor*
Plugin::createEditor()
{
    return new juce::GenericAudioProcessorEditor(*this);
}


juce::AudioProcessor*
JUCE_CALLTYPE createPluginFilter()
{
    return new Plugin();
}
