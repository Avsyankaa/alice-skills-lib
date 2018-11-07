namespace Alice {
class Meta {
public:
    Meta(std::string Locale, std::string Timezone, std::string ClientId); //конструктор класса Meta
    std::string Locale() const;
    std::string Timezone() const;
    std::string ClientId() const;
};
}