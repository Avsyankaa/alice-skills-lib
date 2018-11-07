namespace Alice {
class Session {
public:
    Session (boost::optional<bool> IsNew, size_t MessageId, std::string SessionId, boost::optional<std::string> SkillId, std::string UserId); // Конструктор класса Session для Requets
    bool IsNew() const;
    size_t MessageId() const;
    std::string SessionId() const;
    std::string SkillId() const;
    std::string UserId() const;
};
}